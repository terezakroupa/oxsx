#ifndef __OXSX_EVENT_SCALE__
#define __OXSX_EVENT_SCALE__
#include <EventSystematic.h>
#include <vector>

class EventScale : public EventSystematic{
 public:
    EventScale(); 
    virtual EventData operator()(const EventData&);

    virtual void   SetParameters(const std::vector<double>&);
    virtual void   SetParameter(size_t index_, double val_);
    virtual double GetParameter(size_t index_) const;

    void   SetScale(double);
    double GetScale() const;
    
    virtual void SetDataRep(const DataRepresentation&);
};
#endif
