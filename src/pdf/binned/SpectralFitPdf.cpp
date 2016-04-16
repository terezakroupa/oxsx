#include <SpectralFitPdf.h>
#include <SystematicExceptions.h>

void
SpectralFitPdf::MakeFittable(){
    fHistogram.MakeFittable();
}

std::vector<std::string> 
SpectralFitPdf::GetParameterNames() const{
    return fHistogram.GetParameterNames();
}

std::vector<double> 
SpectralFitPdf::GetParameters() const{
    return fHistogram.GetParameters();
}

size_t
SpectralFitPdf::GetParameterCount() const{
    return fHistogram.GetParameterCount();
}

void
SpectralFitPdf::SetParameters(const std::vector<double>& params_){
    try{
        fHistogram.SetParameters(params_);
    }
    catch(const WrongNumberOfParameters&){
        throw WrongNumberOfParameters("SpectralFitPdf passed wrong number of parameters, is it fittable?");
    }
}

