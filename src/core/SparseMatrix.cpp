#include  <SparseMatrix.h>
#include  <iostream>
#include  <Exceptions.h>

// Initialise the detector response to zero
void 
SparseMatrix::SetAxes(const AxisCollection& axes_){
    fAxes  = axes_;
    fNBins = axes_.GetNBins();
    fNDims = axes_.GetNDimensions();
    fArmaMat = arma::sp_mat(fNBins, fNBins);
}


const AxisCollection& 
SparseMatrix::GetAxes() const{
    return fAxes;
}

void 
SparseMatrix::SetResponse(const arma::sp_mat& response_){
    fArmaMat = response_;
}

void 
SparseMatrix::SetComponent(size_t col_, size_t row_, double val_){
    if (col_ >= fNBins || row_ >= fNBins)
        throw NotFoundError(Formatter() << "Attempted out of bounds access on response matrix (" << row_ <<  "," << col_ << "). Is it initialised with axes?");

    fArmaMat(col_,row_) = val_; 
}

double 
SparseMatrix::GetComponent(size_t col_, size_t row_) const{
    if (col_ >= fNBins || row_ >= fNBins)
        throw NotFoundError(Formatter() << "Attempted out of bounds access on response matrix (" << row_ <<  "," << col_ << "). Is it initialised with axes?");

    return fArmaMat(col_, row_);
}

std::vector<double>
SparseMatrix::operator() (const std::vector<double>& input_) const{
    if (!fNDims){
        throw DimensionError("SparseMatrix::operator() :  NDims = 0, have you set the axes?");
    }
    
    if(fNBins != input_.size()){
        throw DimensionError(Formatter() << "SparseMatrix::opeator() : Input vector ("
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
        throw DimensionError(Formatter() << "SparseMatrix::operator() : matrix multiplation failed. Pdf has "
                             << input_.size() << " bins, but matrix built for " << fAxes.GetNBins()
                             );
    }

    // armadillo function for quick transfer to std::vector double
    return arma::conv_to<std::vector<double> >::from((newContents));
}

SparseMatrix
SparseMatrix::operator*=(const SparseMatrix& other_){
  fArmaMat = fArmaMat * other_.fArmaMat;
  return *this;
}

void
SparseMatrix::SetZeros(){
    if(!fNBins)
        return;
    fArmaMat = arma::sp_mat(fNBins, fNBins);
}

// FIXME: unsigned vs. size_t
void 
SparseMatrix::SetComponents(const std::vector<unsigned>& rowIndices_,
                          const std::vector<unsigned>& colIndices_,
                          const std::vector<double>& values_){
    if(rowIndices_.size() != values_.size() || colIndices_.size() != values_.size())
        throw DimensionError("SparseMatrix::SetComponent() #values != #locations");

    arma::umat locs(2, rowIndices_.size());
    locs.row(0) = arma::urowvec(rowIndices_);
    locs.row(1) = arma::urowvec(colIndices_);

    fArmaMat = arma::sp_mat(locs, arma::vec(values_));
}
