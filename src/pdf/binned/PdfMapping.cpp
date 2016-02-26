#include <PdfMapping.h>
#include <BinnedPdf.h>
#include <iostream>
#include <PdfExceptions.h>

// Initialise the detector response to zero
void 
PdfMapping::SetAxes(const AxisCollection& axes_){
    fAxes  = axes_;
    fNBins = axes_.GetNBins();
    fNDims = axes_.GetNDimensions();
    fResponse = arma::sp_mat(fNBins, fNBins);
}


const AxisCollection& 
PdfMapping::GetAxes() const{
    return fAxes;
}

void 
PdfMapping::SetResponse(const arma::sp_mat& response_){
    fResponse = response_;
}

void 
PdfMapping::SetComponent(size_t col_, size_t row_, double val_){
    if (col_ >= fNBins || row_ >= fNBins)
        throw OutOfBoundsError("Attempted out of bounds access on response matrix! is it initialised with axes?");

    fResponse(col_,row_) = val_; 
}

double 
PdfMapping::GetComponent(size_t col_, size_t row_) const{
    if (col_ >= fNBins || row_ >= fNBins)
        throw OutOfBoundsError("Attempted out of bounds access on response matrix! is it initialised with axes?");

    return fResponse(col_, row_);
}

BinnedPdf
PdfMapping::operator()
    (const BinnedPdf& pdf_) const{
    // FIXME Factor out the bin index manipulation into seperate function or into fAxes class?
    // nneds a addbincontent(<vec of indicies>, content) function to tidy this up

    if (!fNDims){
        throw DimensionError("Empty PdfMap cannpt be used axes! Needs bins to act on!");
    }
    
    if(pdf_.GetNDims() < fNDims){
        throw DimensionError("Pdf Dimensionality too small for PdfMap to act on");
    }


    BinnedPdf observedPdf(pdf_.GetAxes());
    observedPdf.SetDataRep(pdf_.GetDataRep());
    
    // convert to armadillo vec
    arma::vec newContents = fResponse * arma::vec(pdf_.GetBinContents());
    // armadillo function for quick transfer to std::vector double
    observedPdf.SetBinContents(arma::conv_to<std::vector<double> >::from((newContents)));
       
    return observedPdf;
}

PdfMapping
PdfMapping::operator*=(const PdfMapping& other_){
  fResponse = fResponse * other_.fResponse;
  return *this;
}

void
PdfMapping::SetZeros(){
    if(!fNBins)
        return;
    fResponse = arma::sp_mat(fNBins, fNBins);
}

// FIXME: unsigned vs. size_t
void 
PdfMapping::SetComponents(const std::vector<unsigned>& rowIndices_,
                          const std::vector<unsigned>& colIndices_,
                          const std::vector<double>& values_){
    if(rowIndices_.size() != values_.size() || colIndices_.size() != values_.size())
        throw DimensionError("PdfMapping::SetComponent() #values != #locations");

    arma::umat locs(2, rowIndices_.size());
    locs.row(0) = arma::urowvec(rowIndices_);
    locs.row(1) = arma::urowvec(colIndices_);

    fResponse = arma::sp_mat(locs, arma::vec(values_));
}
