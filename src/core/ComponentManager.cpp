#include <ComponentManager.h>

void 
ComponentManager::AddComponent(TunableComponent*  componentPtr_){
    fComponents.push_back(componentPtr_);
    fParamCounts.push_back(componentPtr_ -> GetParameterCount());
    fTotalParamCount += componentPtr_    -> GetParameterCount();
    fComponentCount++;
}

void 
ComponentManager::SetParameters(const std::vector<double>& params_){
    if(params_.size() != fTotalParamCount)
        throw 0;
    if(!params_.size())
        return;

    std::vector<double>::const_iterator it = params_.begin();
    fComponents[0] -> SetParameters(std::vector<double>(it, it + fParamCounts.at(0)));
    for(size_t i = 1; i < fComponents.size(); i++){
        fComponents[i] -> SetParameters(std::vector<double>(it + fParamCounts.at(i-1),
                                                             it  + fParamCounts.at(i-1) +
                                                             + fParamCounts.at(i)));
    }
}

std::vector<double> 
ComponentManager::GetParameters() const{
    std::vector<double> params;
    for(size_t i = 0; i < fComponents.size(); i++){
        const std::vector<double>& comps = fComponents.at(i) -> GetParameters();
                params.insert(params.end(), comps.begin(), comps.end());
    }
    return params;
}

