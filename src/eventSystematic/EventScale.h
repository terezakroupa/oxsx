#ifndef __OXSX_EVENT_SCALE__
#define __OXSX_EVENT_SCALE__
#include <EventSystematic.h>
#include <FitComponent.h>
#include <vector>

class EventScale : public EventSystematic{
 public:
 EventScale() : fScale(1), fScaleName() {}  
    virtual Event operator()(const Event&);

    void   SetScale(double);
    double GetScale() const;

    // Fit Component Interface - just the scale parameter, set directly
    void MakeFittable() {}
    std::vector<std::string> GetParameterNames() const;
    void   SetParameterNames(const std::vector<std::string>&);

    std::vector<double> GetParameters() const;
    void   SetParameters(const std::vector<double>&);
    size_t GetParameterCount() const;

    double GetParameter(const std::string&) const;
    void   SetParameter(const std::string&, double);
    
 private:
    double fScale;
    std::string fScaleName;
};
#endif
