#include <Function.h>
#include <PdfExceptions.h>
void
Function::SetNDims(unsigned nDims_){
    fNDims = nDims_;    
}

unsigned 
Function::GetNDims() const{
    return fNDims;
}

double
Function::Call1D(double val_) const{
    return this->operator()(std::vector<double>(1, val_));
}

void
Function::SetParameters(const std::vector<double>& params_){
    fParams = params_;
}

std::vector<double>
Function::GetParameters() const{
    return fParams;
}


void
Function::SetParameter(size_t index_, double val_){
    if (index_ >= fParams.size())
        throw ParameterError("Tried setting a parameter function does not have!"                             );
    fParams[index_] = val_;
}

double
Function::GetParameter(size_t index_) const{
    try{
        return fParams.at(index_);
    }
    catch(std::out_of_range&){
        throw DimensionError("Tried accessing a parameter function does not have!"                             );
    }
}

