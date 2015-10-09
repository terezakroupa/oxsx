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
    fResponse = arma::mat(fNBins, fNBins, arma::fill::zeros);
}


const AxisCollection& 
PdfMapping::GetAxes() const{
    return fAxes;
}

void 
PdfMapping::SetResponse(const arma::mat& response_){
    fResponse = response_;
}


void 
PdfMapping::SetRow(size_t index_, const std::vector<double>& row_){
    if (index_ >= fNBins)
        throw OutOfBoundsError("Attempted out of bounds access on response matrix! is it initialised with axes?");
    fResponse.row(index_) = arma::vec(row_);
}

void PdfMapping::SetColumn(size_t index_, const std::vector<double>& col_){
    if (index_ >= fNBins)
        throw OutOfBoundsError("Attempted out of bounds access on response matrix! is it initialised with axes?");

    fResponse.col(index_) = arma::vec(col_);
    }


void PdfMapping::SetComponent(size_t col_, size_t row_, double val_){
    if (col_ >= fNBins || row_ >= fNBins)
        throw OutOfBoundsError("Attempted out of bounds access on response matrix! is it initialised with axes?");

    fResponse(col_,row_) = val_; 
}

double PdfMapping::GetComponent(size_t col_, size_t row_) const{
    if (col_ >= fNBins || row_ >= fNBins)
        throw OutOfBoundsError("Attempted out of bounds access on response matrix! is it initialised with axes?");

    return fResponse(col_, row_);
}

PdfMapping PdfMapping::operator = (const PdfMapping& other_){
    if(this != &other_){
        fAxes  = other_.fAxes;
        fNBins = other_.fNBins;
        fNDims = other_.fNDims;
        fResponse = other_.fResponse;
    }
    return *this;
}

BinnedPdf PdfMapping::operator()
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
