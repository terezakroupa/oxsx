#include <SpectralFitPdf.h>
#include <Exceptions.h>
#include <sstream>

std::vector<std::string> 
SpectralFitPdf::GetParameterNames() const{
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
SpectralFitPdf::GetParameters() const{
    return fHistogram.GetBinContents();
}

size_t
SpectralFitPdf::GetParameterCount() const{
    return fHistogram.GetNBins();
}

void
SpectralFitPdf::SetParameters(const std::vector<double>& params_){
    try{
        fHistogram.SetBinContents(params_);
    }
    catch(const NotFoundError&){
        throw ParameterCountError("SpectralFitPdf", GetNBins(), 
                                  params_.size(), "is it fittable?");
    }
}

