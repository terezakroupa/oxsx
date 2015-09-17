#include <SystematicManager.h>

const std::vector<Systematic>& 
SystematicManager::GetSystematics() const{
    return fSystematics;
}

void
SystematicManager::SetParameters(const std::vector<double>& params_){
    fParams = params_;
    std::vector<double>::const_iterator it = params_.begin();
    fSystematics[0].SetParameters(std::vector<double>(it, it + fParamCounts.at(0)));
    for(size_t i = 1; i < fSystematics.size(); i++)
        fSystematics[i].SetParameters(std::vector<double>(it + fParamCounts.at(i-1), 
                                                          it + fParamCounts.at(i)));
}
                                        

const std::vector<double>& 
SystematicManager::GetParameters() const{
    return fParams;
}

void 
SystematicManager::Add(const Systematic& systematic_){
    fSystematics.push_back(systematic_);
    fParamCounts.push_back(systematic_.GetParamCount());
}

