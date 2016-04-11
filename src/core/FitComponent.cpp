#include <FitComponent.h>
#include <SystematicExceptions.h>
//////////////////////
// PUBLIC INTERFACE //
//////////////////////

FitComponent::~FitComponent(){
    for(size_t i = 0; i < fParamPtrs.size(); i++)
        delete fParamPtrs[i];
}

void
FitComponent::SetParameterValues(const std::vector<double>& vals_){
    if(vals_.size() != fNParams)
        throw WrongNumberOfParameters("FitComponent::SetParameterValues!");

    for(size_t i = 0; i < vals_.size(); i++)
        fParamPtrs.at(i) -> Set(vals_.at(i));
}

std::vector<double>
FitComponent::GetParameterValues() const{
    std::vector<double> params;
    params.reserve(fParamPtrs.size());

    for(size_t i = 0; i < fParamPtrs.size(); i++)
        params.push_back(fParamPtrs.at(i)->Get());
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
FitComponent::AddAsParameter(FitParameter* paramPtr_, 
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


