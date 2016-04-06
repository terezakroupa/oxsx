#include <TunableComponent.h>

void
TunableComponent::Empty(){
    fParamPtrs.clear();
    fParamNames.clear();
    fNParams = 0;
}

void 
TunableComponent::AddAsParameter(double* paramPtr_, 
                                 const std::string& name_){
    fParamPtrs.push_back(paramPtr_);
    fParamNames.push_back(name_);
    fNParams++;
}

void
TunableComponent::SetParameters(const std::vector<double>& vals_){
    for(size_t i = 0; i < vals_.size(); i++)
        *(fParamPtrs.at(i)) = vals_.at(i);
}

std::vector<double>
TunableComponent::GetParameters() const{
    std::vector<double> params;
    params.reserve(fParamPtrs.size());

    for(size_t i = 0; i < fParamPtrs.size(); i++)
        params.push_back(*(fParamPtrs.at(i)));
    return params;
}

int 
TunableComponent::GetParameterCount() const{
    return fNParams;
}

