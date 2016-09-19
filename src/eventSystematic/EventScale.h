#ifndef __OXSX_EVENT_SCALE__
#define __OXSX_EVENT_SCALE__
#include <EventSystematic.h>
#include <FitComponent.h>
#include <vector>

class EventScale : public EventSystematic{
 public:
    EventScale() : fScale(1) {}  
    virtual Event operator()(const Event&);

    void   SetScale(double);
    double GetScale() const;

    // Fit Component Interface - just the scale parameter, set directly
    void MakeFittable() {}
    std::vector<std::string> GetParameterNames() const;
    std::vector<double> GetParameters() const;
    size_t GetParameterCount() const;
    void   SetParameters(const std::vector<double>&);

 private:
    double fScale;
};
#endif
