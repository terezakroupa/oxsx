#include <BinnedPdf.h>
#include <iostream>
#include <PdfExceptions.h>
#include <DataExceptions.h>

BinnedPdf::BinnedPdf(const AxisCollection& axes_){
    SetAxes(axes_);
}

BinnedPdf::BinnedPdf(const BinnedPdf& other_) : Pdf(other_){
    fAxes = other_.fAxes;
    fNDims = other_.fNDims;
    fBinContents = other_.fBinContents;
    fNBins = fBinContents.size();
    fDataRep = other_.fDataRep;
}

void 
BinnedPdf::SetAxes(const AxisCollection& axes_){
    fAxes  = axes_;
    fNBins = fAxes.GetNBins();
    fNDims = fAxes.GetNDimensions();
    fBinContents.resize(fNBins, 0);
    
}

const AxisCollection& 
BinnedPdf::GetAxes() const{
    return fAxes;
}

double 
BinnedPdf::operator() (const std::vector<double>& vals_) const{
    return fBinContents.at(FindBin(vals_));
}

double 
BinnedPdf::Integral() const{
    double sum = 0;
    for(size_t i = 0; i < fNBins; i++)
        sum += fBinContents[i];
    return sum;
}

void 
BinnedPdf::Normalise(){
    double sum = Integral();
    for(size_t i = 0; i < fNBins; i++)
        fBinContents[i] /= sum;
}

Pdf* 
BinnedPdf::Clone() const{
    return static_cast<Pdf*>(new BinnedPdf(*this));
}

void 
BinnedPdf::Fill(const std::vector<double>& vals_, double weight_){
    if(vals_.size() != fNDims)
        throw DimensionError("Tried to fill pdf with wrong number of vals");

    fBinContents[FindBin(vals_)] += weight_;
}

void 
BinnedPdf::Fill(const EventData& data_, double weight_){
    try{
        Fill(data_.ToRepresentation(fDataRep), weight_);
    }
    catch (const DimensionError& e_){
        throw RepresentationError(std::string("Representation in compatible with pdf ") + e_.what());
    }
}

void 
BinnedPdf::Fill(double vals_, double weight_){
    Fill(std::vector<double>(1, vals_), weight_);
}

size_t 
BinnedPdf::FindBin(const std::vector<double>& vals_) const{
    return fAxes.FindBin(vals_);
    
}

size_t 
BinnedPdf::FindBin(const EventData& data_) const{
    return fAxes.FindBin(data_.ToRepresentation(fDataRep));    
}

double 
BinnedPdf::GetBinContent(size_t bin_) const{
    if(bin_ > fNBins)
        throw OutOfBoundsError("Out of bounds bin access attempted!");
    return fBinContents[bin_];
}

void 
BinnedPdf::AddBinContent(size_t bin_, double content_){
    if(bin_ > fNBins)
        throw OutOfBoundsError("Tried to add bin contents to non existent bin");
    fBinContents[bin_] += content_;
}

void 
BinnedPdf::SetBinContent(size_t bin_, double content_){
    if(bin_ > fNBins)
        throw OutOfBoundsError("Tried to set contents of non-existent bin");
    fBinContents[bin_] = content_;
}

size_t 
BinnedPdf::GetNBins() const{
    return fNBins;
}

void 
BinnedPdf::Empty(){
    for(size_t i = 0; i < fNBins; i++)
        fBinContents[i] = 0;
}

size_t 
BinnedPdf::FlattenIndicies(const std::vector<size_t>& indicies_) const{
    return fAxes.FlattenIndicies(indicies_);
}

std::vector<size_t> 
BinnedPdf::UnpackIndicies(size_t bin_) const{
    return fAxes.UnpackIndicies(bin_);
}

std::vector<double> 
BinnedPdf::GetData() const{
    return fBinContents;
}
void 
BinnedPdf::SetData(const std::vector<double>& data_){
    if (data_.size() != fNBins)
        throw BinError("Set data that doesn't match binned pdf binning");
    fBinContents = data_;
}

std::vector<double>
BinnedPdf::Means() const{
    std::vector<double> means(fNDims, 0);    
    for(size_t i = 0; i < fNBins; i++)
        for(size_t j = 0; j < fNDims; j++)
            means[j] += fBinContents.at(i) * fAxes.GetBinCentre(i, j);
    return means;
}

std::vector<double>
BinnedPdf::Variances() const{
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
