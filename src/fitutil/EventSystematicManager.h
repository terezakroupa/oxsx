#ifndef __EVENT_SYSTEMATIC_MANAGER__
#define __EVENT_SYSTEMATIC_MANAGER__
#include <vector>

class EventSystematic;
class EventData;
class EventSystematicManager{
 public:    
    EventData ApplySystematics(const EventData&) const;

    void Clear();
    void Add(EventSystematic*);
    const std::vector<EventSystematic*>& GetSystematics() const;
    size_t GetNSystematics() const;

 private:
    std::vector<EventSystematic*> fSystematics;
};

#endif
