#ifndef __OXSX_EVENT_SHIFT__
#define __OXSX_EVENT_SHIFT__
#include <EventSystematic.h>
#include <FitComponent.h>
#include <vector>

class EventShift : public EventSystematic{
 public:
    EventShift() : fShift(0) {}
    EventData operator()(const EventData&);
    
    void   SetShift(double);
    double GetShift() const;

    // FitComponent Interface - just the shift, set directly
    void MakeFittable() {}
    std::vector<std::string> GetParameterNames() const;
    std::vector<double> GetParameters() const;
    size_t GetParameterCount() const;
    void   SetParameters(const std::vector<double>&);

 private:
    double fShift;
};
#endif
