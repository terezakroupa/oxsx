#include <FitComponent.h>
#include <SystematicExceptions.h>
//////////////////////
// PUBLIC INTERFACE //
//////////////////////

void
FitComponent::SetParameterValues(const std::vector<double>& vals_){
    for(size_t i = 0; i < vals_.size(); i++)
        *(fParamPtrs.at(i)) = vals_.at(i);
}

std::vector<double>
FitComponent::GetParameterValues() const{
    std::vector<double> params;
    params.reserve(fParamPtrs.size());

    for(size_t i = 0; i < fParamPtrs.size(); i++)
        params.push_back(*(fParamPtrs.at(i)));
    return params;
}

std::vector<std::string>
FitComponent::GetParameterNames() const{
    return fParamNames;
}

int 
FitComponent::GetParameterCount() const{
    return fNParams;
}


/////////////////////////
// PROTECTED INTERFACE //
/////////////////////////

void 
FitComponent::AddAsParameter(double* paramPtr_, 
                             const std::string& name_){
    fParamPtrs.push_back(paramPtr_);
    fParamNames.push_back(name_);
    fNParams++;
}


void
FitComponent::Empty(){
    fParamPtrs.clear();
    fParamNames.clear();
    fNParams = 0;
}


void
FitComponent::DelegateFor(FitComponent* other_){
    fNParams    = other_->fNParams;
    fParamNames = other_->fParamNames;
    fParamPtrs  = other_->fParamPtrs;
}

void
FitComponent::SetParameterNames(const std::vector<std::string>& names_){
    if(names_.size() != fNParams)
        throw WrongNumberOfParameters("FitComponent::SetParameterNames(-) : wrong number of names!");
    fParamNames = names_;
}
