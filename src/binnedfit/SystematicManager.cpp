#include <SystematicManager.h>
#include <SystematicExceptions.h>

const std::vector<Systematic*>& 
SystematicManager::GetSystematics() const{
    return fSystematics;
}

void
SystematicManager::SetParameters(const std::vector<double>& params_){
    // No parameters or no change? dont do anything
    if (!params_.size() || params_ == fParams)
        return;

    // wrong number of parameters
    if (params_.size() != fTotalParamCount)
        throw WrongNumberOfParameters("Fit routine passed wrong number of systematic params!");

    fParams = params_;

    // divide up the systematics into their proper destination
    std::vector<double>::const_iterator it = params_.begin();
    fSystematics[0] -> SetParameters(std::vector<double>(it, it + fParamCounts.at(0)));

    for(size_t i = 1; i < fSystematics.size(); i++){
        fSystematics[i] -> SetParameters(std::vector<double>(it + fParamCounts.at(i-1), 
                                                             it  + fParamCounts.at(i-1) + 
                                                             + fParamCounts.at(i)));
    }

    for(size_t i = 0; i < fSystematics.size(); i++)
        fSystematics[i] -> Construct();

}


                                        

const std::vector<double>& 
SystematicManager::GetParameters() const{
    return fParams;
}

void 
SystematicManager::Add(Systematic* systematic_){    
    fSystematics.push_back(systematic_);
    fParamCounts.push_back(systematic_->GetParamCount());
    fTotalParamCount += systematic_->GetParamCount();
    fNSystematics++;
}

size_t
SystematicManager::GetNSystematics() const{
    return fNSystematics;
}
