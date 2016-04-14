#include <ContainerParameter.h>
#include <FitComponent.h>
#include <SystematicExceptions.h>
#include <iostream>
#include <sstream>

//////////////////////
// PUBLIC INTERFACE //
//////////////////////

FitComponent::~FitComponent(){
    for(size_t i = 0; i < fParamPtrs.size(); i++)
        delete fParamPtrs[i];
}

void
FitComponent::SetParameterValues(const std::vector<double>& vals_){
    MakeFittable();
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
FitComponent::EmptyParameters(){
    fParamPtrs.clear();
    fParamNames.clear();
    fNParams = 0;
}


void
FitComponent::DelegateFor(FitComponent* other_){
    other_      -> MakeFittable();
    fNParams    = other_->fNParams;
    fParamNames = other_->fParamNames;
    for(size_t i = 0; i < other_->GetParameterCount(); i++)
        fParamPtrs.push_back(other_->fParamPtrs[i]->Clone());
}

void
FitComponent::SetParameterNames(const std::vector<std::string>& names_){
    MakeFittable();
    if(names_.size() != fNParams)
        throw WrongNumberOfParameters("FitComponent::SetParameterNames(-) : wrong number of names!");
    fParamNames = names_;
}


