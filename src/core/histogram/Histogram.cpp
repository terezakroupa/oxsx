#include <Histogram.h>
#include <iostream>
#include <PdfExceptions.h>
#include <DataExceptions.h>

Histogram::Histogram(const AxisCollection& axes_){
    SetAxes(axes_);
}

Histogram::Histogram(const Histogram& other_){
    fAxes = other_.fAxes;
    fNDims = other_.fNDims;
    fBinContents = other_.fBinContents;
    fNBins = fBinContents.size();
}

void 
Histogram::SetAxes(const AxisCollection& axes_){
    fAxes  = axes_;
    fNBins = fAxes.GetNBins();
    fNDims = fAxes.GetNDimensions();
    fBinContents.resize(fNBins, 0);
    
}

const AxisCollection& 
Histogram::GetAxes() const{
    return fAxes;
}

double 
Histogram::operator() (const std::vector<double>& vals_) const{
    return fBinContents.at(FindBin(vals_));
}

double 
Histogram::Integral() const{
    double sum = 0;
    for(size_t i = 0; i < fNBins; i++)
        sum += fBinContents[i];
    return sum;
}

void 
Histogram::Normalise(){
    double sum = Integral();
    for(size_t i = 0; i < fNBins; i++)
        fBinContents[i] /= sum;
}

void 
Histogram::Fill(const std::vector<double>& vals_, double weight_){
    if(vals_.size() != fNDims)
        throw DimensionError("Tried to fill pdf with wrong number of vals");

    fBinContents[FindBin(vals_)] += weight_;
}


void 
Histogram::Fill(double vals_, double weight_){
    Fill(std::vector<double>(1, vals_), weight_);
}

size_t 
Histogram::FindBin(const std::vector<double>& vals_) const{
    return fAxes.FindBin(vals_);
    
}

double 
Histogram::GetBinContent(size_t bin_) const{
    if(bin_ > fNBins)
        throw OutOfBoundsError("Out of bounds bin access attempted!");
    return fBinContents[bin_];
}

void 
Histogram::AddBinContent(size_t bin_, double content_){
    if(bin_ > fNBins)
        throw OutOfBoundsError("Tried to add bin contents to non existent bin");
    fBinContents[bin_] += content_;
}

void 
Histogram::SetBinContent(size_t bin_, double content_){
    if(bin_ > fNBins)
        throw OutOfBoundsError("Tried to set contents of non-existent bin");
    fBinContents[bin_] = content_;
}

size_t 
Histogram::GetNBins() const{
    return fNBins;
}

void 
Histogram::Empty(){
    for(size_t i = 0; i < fNBins; i++)
        fBinContents[i] = 0;
}

size_t 
Histogram::FlattenIndicies(const std::vector<size_t>& indicies_) const{
    return fAxes.FlattenIndicies(indicies_);
}

std::vector<size_t> 
Histogram::UnpackIndicies(size_t bin_) const{
    return fAxes.UnpackIndicies(bin_);
}

std::vector<double> 
Histogram::GetBinContents() const{
    return fBinContents;
}
void 
Histogram::SetBinContents(const std::vector<double>& data_){
    if (data_.size() != fNBins)
        throw BinError("Set data that doesn't match binned pdf binning");
    fBinContents = data_;
    fNBins = fBinContents.size();
}

std::vector<double>
Histogram::Means() const{
    std::vector<double> means(fNDims, 0);    
    for(size_t i = 0; i < fNBins; i++)
        for(size_t j = 0; j < fNDims; j++)
            means[j] += fBinContents.at(i) * fAxes.GetBinCentre(i, j);
    return means;
}

std::vector<double>
Histogram::Variances() const{
    std::vector<double> variances(fNDims, 0);

    for(size_t i = 0; i < fNBins; i++)
        for(size_t j = 0; j < fNDims; j++){
            double binCent = fAxes.GetBinCentre(i, j);
            variances[j] += binCent * binCent *  fBinContents.at(i);
        }
    
    

    std::vector<double> means = Means();
    for(size_t i = 0; i < fNDims; i++)
        variances[i] -= means.at(i) * means.at(i);

    return variances;
}
