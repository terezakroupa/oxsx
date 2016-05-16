#include <EventSystematicManager.h>
#include <EventSystematic.h>
#include <SystematicExceptions.h>
#include <EventData.h>

void 
EventSystematicManager::Clear(){
    fSystematics.clear();
}

void
EventSystematicManager::Add(EventSystematic* sys_){
    fSystematics.push_back(sys_);
}

const std::vector<EventSystematic*>& 
EventSystematicManager::GetSystematics() const{
    return fSystematics;
}


size_t 
EventSystematicManager::GetNSystematics() const{
    return fSystematics.size();
}

EventData 
 EventSystematicManager::ApplySystematics(const EventData& event_) const{
    EventData modified = event_;
    for(size_t i = 0; i < fSystematics.size(); i++)
        modified = fSystematics.at(i)->operator()(modified);
    return modified;
}
