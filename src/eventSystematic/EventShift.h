#ifndef __OXSX_EVENT_SHIFT__
#define __OXSX_EVENT_SHIFT__
#include <EventSystematic.h>
#include <vector>

class EventShift : public EventSystematic{
 public:
    virtual EventData operator()(const EventData&);

    virtual void   SetParameters(const std::vector<double>&);
    virtual void   SetParameter(size_t index_, double val_);
    virtual double GetParameter(size_t index_) const;

    void   SetShift(double);
    double GetShift() const;
    
    virtual void SetDataRep(const DataRepresentation&);
};
#endif
