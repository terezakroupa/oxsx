#include <BinnedPdf.h>
#include <iostream>
BinnedPdf::BinnedPdf(const AxisCollection& axes_){
    SetAxes(axes_);
}

BinnedPdf::BinnedPdf(const BinnedPdf& other_) : Pdf(other_){
    fAxes = other_.fAxes;
    fNDims = other_.fNDims;
    fBinContents = other_.fBinContents;
    fNBins = fBinContents.size();
}

void BinnedPdf::SetAxes(const AxisCollection& axes_){
    fAxes  = axes_;
    fNBins = fAxes.GetNBins();
    fNDims = fAxes.GetNDimensions();
    fBinContents.resize(fNBins, 0);
    
}

AxisCollection BinnedPdf::GetAxes() const{
    return fAxes;
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

void BinnedPdf::Fill(const DataHandler& data_){
    Fill(data_.ToRepresentation(fDataRep));
}

size_t BinnedPdf::FindBin(const std::vector<double>& vals_) const{
    return fAxes.FindBin(vals_);
    
}

double BinnedPdf::GetBinContent(size_t bin_) const{
    if(bin_ > fNBins)
        throw 0; //FIXME should be outofbounds error
    return fBinContents[bin_];
}

void BinnedPdf::AddBinContent(size_t bin_, double content_){
    if(bin_ > fNBins)
        throw 0; //FIXME should be outofbounds error
    fBinContents[bin_] += content_;
}

size_t BinnedPdf::GetNBins() const{
    return fNBins;
}

void BinnedPdf::Empty(){
    for(size_t i = 0; i < fNBins; i++)
        fBinContents[i] = 0;
}

size_t BinnedPdf::FlattenIndicies(const std::vector<size_t>& indicies_) const{
    return fAxes.FlattenIndicies(indicies_);
}

std::vector<size_t> BinnedPdf::UnpackIndicies(size_t bin_) const{
    return fAxes.UnpackIndicies(bin_);
}
