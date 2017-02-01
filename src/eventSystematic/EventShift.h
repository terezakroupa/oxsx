#ifndef __OXSX_EVENT_SHIFT__
#define __OXSX_EVENT_SHIFT__
#include <EventSystematic.h>
#include <FitComponent.h>
#include <vector>

class EventShift : public EventSystematic{
 public:
    EventShift() : fShift(0) {}
    Event operator()(const Event&);
    
    void   SetShift(double);
    double GetShift() const;

    // FitComponent Interface - just the shift, set directly
    void MakeFittable() {}
    std::vector<std::string> GetParameterNames() const;
    void   SetParameterNames(const std::vector<std::string>&);

    std::vector<double> GetParameters() const;
    size_t GetParameterCount() const;
    void   SetParameters(const std::vector<double>&);

    double GetParameter(const std::string&) const;
    void   SetParameter(const std::string&, double);

 private:
    double fShift;
    std::string fShiftName;
};
#endif
