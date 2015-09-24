#include <IntegrablePdf.h>
#include <PdfExceptions.h>

void
IntegrablePdf::SetParameters(const std::vector<double>& params_){
    fParams = params_;
}

std::vector<double>
IntegrablePdf::GetParameters() const{
    return fParams;
}


void
IntegrablePdf::SetParameter(size_t index_, double val_){
    if (index_ >= fParams.size())
        throw ParameterError("Tried accessing a parameter pdf does not have!");
}

double
IntegrablePdf::GetParameter(size_t index_) const{
    try{
        return fParams.at(index_);
    }
    catch(std::out_of_range&){
        throw DimensionError("Tried accessing a parameter pdf does not have!");
    }
}
