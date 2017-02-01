#include <ParameterManager.h>
#include <DoubleParameter.h>
#include <Exceptions.h>
#include <iostream>

ParameterManager::~ParameterManager(){
    for(size_t i = 0; i < fParamPtrs.size(); i++)
        delete fParamPtrs[i];
}

void
ParameterManager::SetParameters(const std::vector<double>& vals_){
    if(vals_.size() != GetParameterCount())
        throw ParameterCountError("ParameterManager", 
                                  GetParameterCount(),
                                  vals_.size());

    for(size_t i = 0; i < vals_.size(); i++)
        fParamPtrs.at(i) -> Set(vals_.at(i));
}

std::vector<double>
ParameterManager::GetParameters() const{
    std::vector<double> params;
    params.reserve(fParamPtrs.size());

    for(size_t i = 0; i < fParamPtrs.size(); i++)
        params.push_back(fParamPtrs.at(i)->Get());
    return params;
}

std::vector<std::string>
ParameterManager::GetParameterNames() const{
    std::vector<std::string> names;
    for(size_t i = 0; i < fParamPtrs.size(); i++)
        names.push_back(fParamPtrs[i] -> GetName());
    return names;
}

void
ParameterManager::SetParameterNames(const std::vector<std::string>& names_){
    if(names_.size() != fParamPtrs.size())
        throw DimensionError("ParameterManager::SetParameterNames",
                             fParamPtrs.size(), names_.size(), "have all the parameters been added?"
                             );
    for(size_t i = 0; i < fParamPtrs.size(); i++)
        fParamPtrs[i] -> SetName(names_.at(i));
}

size_t
ParameterManager::GetParameterCount() const{
    return fParamPtrs.size();
}

// FIXME: This is dodgy, definitely do not forget about this and make it public
FitParameter* 
ParameterManager::FindParameter(const std::string& name_) const{
    for(size_t i = 0; i < fParamPtrs.size(); i++){
        if(fParamPtrs.at(i)->GetName() == name_)
            return fParamPtrs.at(i);
    }
    throw NotFoundError(Formatter() << "Parameter " << name_ << "  not found");
}

double
ParameterManager::GetParameter(const std::string& name_) const{
    return FindParameter(name_)->Get();
}

void
ParameterManager::SetParameter(const std::string& name_, double val_){
    FindParameter(name_)->Set(val_);
}

void 
ParameterManager::Add(FitParameter* p_){
    fParamPtrs.push_back(p_);
}

void 
ParameterManager::AddDouble(double& d_, const std::string& n_){
    fParamPtrs.push_back(new DoubleParameter(n_, d_));
}

void
ParameterManager::Clear(){
    fParamPtrs.clear();
}
