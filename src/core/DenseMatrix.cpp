#include <DenseMatrix.h>
#include <iostream>
#include <Exceptions.h>

// Initialise the detector response to zero
void 
DenseMatrix::SetAxes(const AxisCollection& axes_){
    fAxes  = axes_;
    fNBins = axes_.GetNBins();
    fNDims = axes_.GetNDimensions();
    fArmaMat = arma::mat(fNBins, fNBins);
}


const AxisCollection& 
DenseMatrix::GetAxes() const{
    return fAxes;
}


void 
DenseMatrix::SetComponent(size_t col_, size_t row_, double val_){
    if (col_ >= fNBins || row_ >= fNBins)
        throw NotFoundError(Formatter() << "Attempted out of bounds access on matrix (" << row_ <<  "," << col_ << "). Is it initialised with axes?");

    fArmaMat(col_,row_) = val_; 
}

double 
DenseMatrix::GetComponent(size_t col_, size_t row_) const{
    if (col_ >= fNBins || row_ >= fNBins)
        throw NotFoundError(Formatter() << "Attempted out of bounds access on response matrix (" << row_ <<  "," << col_ << "). Is it initialised with axes?");

    return fArmaMat(col_, row_);
}

std::vector<double>
DenseMatrix::operator() (const std::vector<double>& input_) const{
    if (!fNDims){
        throw DimensionError("DenseMatrix::operator() :  NDims = 0, have you set the axes?");
    }
    
    if(fNBins != input_.size()){
        throw DimensionError(Formatter() << "DenseMatrix::opeator() : Input vector ("
                                         << input_.size() << ")" 
                                         << " wrong size for PdfMap ("
                                         << fNDims
                                         << " ) to act on");
    }

    arma::vec newContents;
    try{
        // convert to armadillo vec
        newContents = fArmaMat * arma::vec(input_);
    }
    catch(const std::logic_error& e_){
        throw DimensionError(Formatter() << "DenseMatrix::operator() : matrix multiplation failed. Pdf has "
                             << input_.size() << " bins, but matrix built for " << fAxes.GetNBins()
                             );
    }

    // armadillo function for quick transfer to std::vector double
    return arma::conv_to<std::vector<double> >::from((newContents));
}

DenseMatrix
DenseMatrix::operator*=(const DenseMatrix& other_){
  fArmaMat = fArmaMat * other_.fArmaMat;
  return *this;
}

void
DenseMatrix::SetZeros(){
    if(!fNBins)
        return;
    fArmaMat = arma::mat(fNBins, fNBins);
}

void
DenseMatrix::SetToIdentity(){
    if(!fNBins)
        return;
    fArmaMat.eye();
}
