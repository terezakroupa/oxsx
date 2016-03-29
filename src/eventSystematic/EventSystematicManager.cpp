#include <EventSystematicManager.h>
#include <SystematicExceptions.h>
#include <EventData.h>

void
EventSystematicManager::Add(EventSystematic* sys_){
    fSystematics.push_back(sys_);
    fParamCounts.push_back(sys_->GetParamCount());
    fTotalParamCount += sys_->GetParamCount();
    fNSystematics++;
}

const std::vector<EventSystematic*>& 
EventSystematicManager::GetSystematics() const{
    return fSystematics;
}

void
EventSystematicManager::SetSystematics(const std::vector<EventSystematic*>& systematics_){
    fSystematics = systematics_;
}


void 
EventSystematicManager::SetParameters(const std::vector<double>& params_){
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
}

const std::vector<double>& 
EventSystematicManager::GetParameters() const{
    return fParams;
}

size_t 
EventSystematicManager::GetNSystematics() const{
    return fSystematics.size();
}

EventData 
EventSystematicManager::ApplySystematics(const EventData& event_) const{
    for(size_t i = 0; i < fSystematics.size(); i++)
        event_ = fSystematics.at(i)->operator()(event_);
}
