#include <SpectralFitPdf.h>
#include <PdfExceptions.h>
#include <SystematicExceptions.h>
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
    catch(const OutOfBoundsError&){
        throw WrongNumberOfParameters("SpectralFitPdf passed wrong number of parameters is it fittable?");
    }
}

