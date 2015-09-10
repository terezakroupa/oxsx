#include <PdfMapping.h>
#include <BinnedPdf.h>
#include <iostream>

void PdfMapping::SetAxes(const AxisCollection& axes_){
    fAxes  = axes_;
    fNBins = axes_.GetNBins();
    fNDims = axes_.GetNDimensions();
    fResponse.resize(fNBins);
    for(size_t i = 0; i < fNBins; i++)
        fResponse[i] = std::vector<double>(fNBins, 0);
}

const AxisCollection& PdfMapping::GetAxes() const{
    return fAxes;
}

void PdfMapping::SetResponse(const std::vector<std::vector<double> >& response_){
    fResponse = response_;
}


void PdfMapping::SetRow(size_t index_, const std::vector<double>& row_){
    fResponse[index_] = row_;
}

void PdfMapping::SetColumn(size_t index_, const std::vector<double>& col_){
    for(size_t i = 0; i < fNBins; i++){
        fResponse[i][index_] = col_[i];
    }
}

void PdfMapping::SetComponent(size_t col_, size_t row_, double val_){
    fResponse[col_][row_] = val_;
}

double PdfMapping::GetComponent(size_t column_, size_t row_) const{
    return fResponse[column_][row_];
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

    if (fNDims == 0){
        std::cout << "No axes! make me match the pdf binning!" << std::endl;
        throw 0; // FIXME should be dim error
    }


    if(pdf_.GetNDims() < fNDims){
        throw 0; // FIXME needs to be dimension error
    }

    BinnedPdf observedPdf(pdf_);
    observedPdf.Empty();
    // FIXME looping variable names so it makes more sense
    for(size_t bin = 0; bin < pdf_.GetNBins(); bin++){
        // Work out which indices you care about 
        std::vector<size_t> pdfIndicies = pdf_.UnpackIndicies(bin);
        std::vector<size_t> relIndicies(indicies_.size(), 0);

        // FIXME catch the out of bounds error below tryig to find an index 
        for(size_t i = 0; i < relIndicies.size(); i++)
            relIndicies[i] = pdfIndicies.at(indicies_.at(i));
        size_t systematicBin = fAxes.FlattenIndicies(relIndicies);
        double content = pdf_.GetBinContent(bin);

        // Loop over the first index and distribute the bin contents
        for(size_t i = 0; i < fResponse.size(); i++){
            double newContent = fResponse[i][systematicBin] * content;
            std::vector<size_t> newSysIndicies = fAxes.UnpackIndicies(i);
            std::vector<size_t> newPdfIndicies(pdfIndicies);
            for(size_t i = 0; i < indicies_.size(); i++)
                newPdfIndicies[indicies_[i]] = newSysIndicies[i];
            size_t pdfBin = pdf_.FlattenIndicies(newPdfIndicies);
            observedPdf.AddBinContent(pdfBin,newContent);
        }
    }
    return observedPdf;
}
