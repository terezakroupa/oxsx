#include "BinnedPdf.h"
#include <sstream>
#include <fstream>
#include <iostream>
BinnedPdf::BinnedPdf(const std::string& name_, AxisCollection axes_){
    fAxes = axes_;
    fName = name_;
    fBinContents.resize(fAxes.GetNBins(),0);
}

double BinnedPdf::operator() (const std::vector<double>* vals_) const{
    return fBinContents.at(fAxes.FindBin(*vals_));
}

double BinnedPdf::operator() (const std::vector<double>* vals_,
                              const std::vector<size_t>& indicies_) const{
    // at the moment this makes a copy.. come back if this proves too slow
    std::vector<double> relevantVals(indicies_.size(), 0);
    for(size_t i =0; i < indicies_.size(); i++)
        relevantVals[i] = vals_->at(indicies_[i]);
    return fBinContents.at(fAxes.FindBin(relevantVals));
}

double BinnedPdf::GetBinContent(size_t bin_) const{
    return fBinContents.at(bin_);
}

double BinnedPdf::GetBinContent(const std::vector<size_t>& indicies_) const{
    return fBinContents.at(fAxes.FlattenIndicies(indicies_));
}

std::string BinnedPdf::GetName() const{
    return fName;
}

double BinnedPdf::Integral() const{
    double sum = 0;
    for(size_t i = 0; i < fBinContents.size(); i++)
        sum += fBinContents.at(i);
    return sum;
}

void BinnedPdf::Normalise(){
    double integral = Integral();
    if (integral)
        for (size_t i = 0; i < fBinContents.size(); i++ )
            fBinContents[i] /= integral;
}

void BinnedPdf::Fill(const std::vector<double>& vals_){
    fBinContents[fAxes.FindBin(vals_)]++;
}

void BinnedPdf::AddBinContent(const std::vector<size_t>& indicies_, double content){
    fBinContents[fAxes.FlattenIndicies(indicies_)] += content;
}

BinnedPdf BinnedPdf::Marginalise(const std::vector<size_t>& axisIndicies_) const{
    if (axisIndicies_.size() > fAxes.GetNDimensions())
        throw DimensionError("Projection has higher dim than parent!");
    for(size_t i = 0; i < axisIndicies_.size(); i++)
        if (axisIndicies_[i] >= fAxes.GetNDimensions())
            throw DimensionError("Requested projection onto non-existent axis!");

    AxisCollection newAxes;
    for(size_t i = 0; i < axisIndicies_.size(); i++)
        newAxes.AddAxis(fAxes.GetAxis(axisIndicies_[i]));

    std::stringstream ss;
    ss << fName << "_projection";
    for(size_t i = 0; i < axisIndicies_.size(); i++)
        ss << "_" << i;
    
    BinnedPdf projection(ss.str(), newAxes);

    for(size_t iBin = 0; iBin < fBinContents.size(); iBin++){
        std::vector<size_t> indicies = fAxes.UnpackIndicies(iBin);

        // pick only the indicies you are interested in
        std::vector<size_t> newIndicies;
        for(size_t iAxis = 0 ; iAxis < axisIndicies_.size(); iAxis++)
            newIndicies.push_back(indicies[axisIndicies_[iAxis]]);        
        projection.AddBinContent(newIndicies, GetBinContent(iBin));
    }                
    return projection;
}

BinnedPdf BinnedPdf::Marginalise(size_t axisIndex_) const{
    std::vector<size_t> sv(1, axisIndex_);
    return Marginalise(sv);
}


std::vector<double> BinnedPdf::GetRawData() const{
    return fBinContents;
}
