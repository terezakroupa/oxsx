#ifndef __EVENT_SYSTEMATIC_MANAGER__
#define __EVENT_SYSTEMATIC_MANAGER__
#include <EventSystematic.h>
#include <vector>

class EventSystematicManager{
 public:
    EventSystematicManager() : fNSystematics(0), fTotalParamCount(0) {}
    ~EventSystematicManager() {}
    
    EventData ApplySystematics(const EventData&) const;

    void Add(EventSystematic*);
    const std::vector<EventSystematic*>& GetSystematics() const;
    void SetSystematics(const std::vector<EventSystematic*>&);

    void SetParameters(const std::vector<double>& params_);
    const std::vector<double>& GetParameters() const;

    size_t GetNSystematics() const;

 private:
    std::vector<EventSystematic*> fSystematics;
    std::vector<size_t> fParamCounts;
    std::vector<double> fParams;
    
    size_t fTotalParamCount;
    size_t fNSystematics;
};

#endif
