#include <SpectralFitDist.h>
#include <Exceptions.h>
#include <sstream>

void
SpectralFitDist::SetParameterBaseName(const std::string& base_){
    fParamNames.clear();
    fParamNames.reserve(fHistogram.GetNBins());
    
    std::stringstream ss;
    for(size_t i = 0; i < fHistogram.GetNBins(); i++){
        ss << base_ << i;
        fParamNames.push_back(ss.str());
        ss.str("");
    }    
}

std::vector<std::string> 
SpectralFitDist::GetParameterNames() const{
    return fParamNames;
}

std::vector<double>
SpectralFitDist::GetParameters() const{
    return fHistogram.GetBinContents();
}

size_t
SpectralFitDist::GetParameterCount() const{
    return fHistogram.GetNBins();
}

void
SpectralFitDist::SetParameters(const std::vector<double>& params_){
    try{
        fHistogram.SetBinContents(params_);
    }
    catch(const NotFoundError&){
        throw ParameterCountError("SpectralFitDist", GetNBins(), 
                                  params_.size(), "is it fittable?");
    }
}

void
SpectralFitDist::SetParameterNames(const std::vector<std::string>& names_){
    if(names_.size() != fHistogram.GetNBins())
        throw DimensionError("SpectralFitDist::SetParameterNames", fHistogram.GetNBins(), names_.size(), 
                             "Need one name for each bin, use SetParameterBaseName('myname'); for bins called myname1 myname2 etc.");
    fParamNames = names_;
}

double
SpectralFitDist::GetParameter(const std::string& name_) const{
    std::vector<std::string>::const_iterator it = std::find(fParamNames.begin(), fParamNames.end(), name_);
    if(it == fParamNames.end())
        throw NotFoundError(Formatter() << "SpectralFitDist::No parameter called " << name_);
    return fHistogram.GetBinContent(it - fParamNames.begin());
}

void
SpectralFitDist::SetParameter(const std::string& name_, double val_){
    std::vector<std::string>::iterator it = std::find(fParamNames.begin(), fParamNames.end(), name_);
    if(it == fParamNames.end())
        throw NotFoundError(Formatter() << "SpectralFitDist::No parameter called " << name_);
    return fHistogram.SetBinContent(it - fParamNames.begin(), val_);
}

