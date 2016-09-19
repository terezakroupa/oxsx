#ifndef __OXSX_EVENT_DISTRIBUTION__
#define __OXSX_EVENT_DISTRIBUTION__
#include <DataRepresentation.h>
#include <EventData.h>
#include <vector>
#include <string>

class EventDistribution{
 public:
    virtual ~EventDistribution() {}
    virtual EventDistribution* Clone() const = 0;

    virtual double Probability(const EventData&) const = 0;
    
    virtual double Integral() const = 0;
    virtual void   Normalise()   = 0;

    virtual unsigned GetNDims() const = 0;    
};
#endif
