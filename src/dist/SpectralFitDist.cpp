#include <SpectralFitDist.h>
#include <Exceptions.h>
#include <sstream>

std::vector<std::string> 
SpectralFitDist::GetParameterNames() const{
    std::vector<std::string> names;
    names.reserve(fHistogram.GetNBins());

    std::stringstream ss;
    for(size_t i = 0; i < fHistogram.GetNBins(); i++){
        ss << "Spectral fit bin " << i;
        names.push_back(ss.str());
        ss.str("");
    }
    return names;
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

