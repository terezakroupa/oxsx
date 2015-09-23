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
    fResponse.resize(fNBins);
    for(size_t i = 0; i < fNBins; i++)
        fResponse[i] = std::vector<double>(fNBins, 0);
}


const AxisCollection& 
PdfMapping::GetAxes() const{
    return fAxes;
}

void 
PdfMapping::SetResponse(const std::vector<std::vector<double> >& response_){
    fResponse = response_;
}


void 
PdfMapping::SetRow(size_t index_, const std::vector<double>& row_){
    if (index_ >= fNBins)
        throw OutOfBoundsError("Attempted out of bounds access on response matrix!");
    fResponse[index_] = row_;
}

void PdfMapping::SetColumn(size_t index_, const std::vector<double>& col_){
    if (index_ >= fNBins)
        throw OutOfBoundsError("Attempted out of bounds access on response matrix!");

    for(size_t i = 0; i < fNBins; i++){
        fResponse[i][index_] = col_[i];
    }
}

void PdfMapping::SetComponent(size_t col_, size_t row_, double val_){
    if (col_ >= fNBins || row_ >= fNBins)
        throw OutOfBoundsError("Attempted out of bounds access on response matrix!");

    fResponse[col_][row_] = val_; 
}

double PdfMapping::GetComponent(size_t col_, size_t row_) const{
    if (col_ >= fNBins || row_ >= fNBins)
        throw OutOfBoundsError("Attempted out of bounds access on response matrix!");

    return fResponse[col_][row_];
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
    (const BinnedPdf& pdf_, const std::vector<size_t>& indicies_) const{
    // FIXME Factor out the bin index manipulation into seperate function or into fAxes class?
    // nneds a addbincontent(<vec of indicies>, content) function to tidy this up

    if (!fNDims){
        throw DimensionError("Empty PdfMap cannpt be used axes! Needs bins to act on!");
    }

    if(pdf_.GetNDims() < fNDims){
        throw DimensionError("Pdf Dimensionality too small for PdfMap to act on");
    }

    /*
      1. Copy the pdf and empty it (bins and data rep will then be the same)
      2. Loop over the global bin ID num, and work out the indicies in the pdf axes
      3. Take from that list the indicies in the dimensions this mapping acts on  (relIndicies)
      4. Flatten into global index of the systematic indicies
      5. Distribute that bins contents across the other bins according to the response matrix
            x'_i += R_ij * x_j
     */


    BinnedPdf observedPdf(pdf_);
    observedPdf.Empty();


    for(size_t pdfGlobalBin = 0; pdfGlobalBin < pdf_.GetNBins(); pdfGlobalBin++){
        // Get the indicies you care about 
        std::vector<size_t> pdfIndicies = pdf_.UnpackIndicies(pdfGlobalBin);
        std::vector<size_t> relIndicies(indicies_.size(), 0);

        try{
            for(size_t i = 0; i < relIndicies.size(); i++)
                relIndicies[i] = pdfIndicies.at(indicies_.at(i));
        }
        catch (std::out_of_range&){
            throw DimensionError("PdfMapping and pdf are incompatible - need to work on same index!");
        }

        size_t systematicBin = fAxes.FlattenIndicies(relIndicies);
        double content = pdf_.GetBinContent(pdfGlobalBin);

        // Loop over the first index and distribute the bin contents
        for(size_t i = 0; i < fResponse.size(); i++){
            double newContent = fResponse[i][systematicBin] * content;
            std::vector<size_t> newSysIndicies = fAxes.UnpackIndicies(i);
            std::vector<size_t> newPdfIndicies(pdfIndicies.size(),0);

            for(size_t i = 0; i < indicies_.size(); i++)
                newPdfIndicies[indicies_[i]] = newSysIndicies[i];

            size_t pdfBin = pdf_.FlattenIndicies(newPdfIndicies);
            observedPdf.AddBinContent(pdfBin,newContent);
        }
    }
    return observedPdf;
}
