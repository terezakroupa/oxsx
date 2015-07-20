#include "BinnedPdf.h"

BinnedPdf::BinnedPdf(const AxisCollection& axes_){
    fAxes = axes_;
    fNDims = axes_.GetNDimensions();
}

BinnedPdf::BinnedPdf(const BinnedPdf& other_){
    fAxes = other_.fAxes;
    fNDims = other_.fNDims;
    fBinContents = other_.fBinContents;
    fNBins = fBinContents.size();
}

double BinnedPdf::operator() (const std::vector<double>& vals_) const{
    return fBinContents.at(FindBin(vals_));
}

double BinnedPdf::Integral() const{
    double sum = 0;
    for(size_t i = 0; i < fNBins; i++)
        sum += fBinContents[i];
    return sum;
}

void BinnedPdf::Normalise(){
    double sum = Integral();
    for(size_t i = 0; i < fNBins; i++)
        fBinContents[i] /= sum;
}

Pdf* BinnedPdf::Clone() const{
    return static_cast<Pdf*>(new BinnedPdf(*this));
}

void BinnedPdf::Fill(const std::vector<double>& vals_){
    fBinContents[FindBin(vals_)]++;
}

size_t BinnedPdf::FindBin(const std::vector<double>& vals_) const{
    return fAxes.FindBin(vals_);
    
}
