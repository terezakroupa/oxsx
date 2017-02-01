#ifndef __OXSX_EVENT_RECONVOLUTION__
#define __OXSX_EVENT_RECONVOLUTION__
#include <EventSystematic.h>
#include <FitComponent.h>

class Event;
class EventReconvolution : public EventSystematic{
 public:
    EventReconvolution() : fCorrection(1){}
    Event operator()(const Event&);

    double GetCorrection() const;
    void   SetCorrection(double);

    // Fit Component Interface - just the correction, set directly
    void  MakeFittable() {}
    std::vector<std::string> GetParameterNames() const;
    void   SetParameterNames(const std::vector<std::string>&);

    std::vector<double> GetParameters() const;
    size_t GetParameterCount() const;
    void   SetParameters(const std::vector<double>&);

    double GetParameter(const std::string&) const;
    void   SetParameter(const std::string&, double);

 private:
    double fCorrection;
    std::string fCorrectionName;
};
#endif
