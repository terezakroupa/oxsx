#include <ParameterManager.h>
#include <SystematicExceptions.h>

ParameterManager::~ParameterManager(){
    for(size_t i = 0; i < fParamPtrs.size(); i++)
        delete fParamPtrs[i];
}

void
ParameterManager::SetParameters(const std::vector<double>& vals_){
    if(vals_.size() != GetParameterCount())
        throw WrongNumberOfParameters("ParameterManager::SetParameterValues!");

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
    return fNames;
}

size_t
ParameterManager::GetParameterCount() const{
    return fParamPtrs.size();
}
