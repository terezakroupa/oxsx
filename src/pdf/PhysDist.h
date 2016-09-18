#ifndef __OXSX_PHYSDIST__
#define __OXSX_PHYSDIST__
#include <vector>
#include <string>
#include <DataRepresentation.h>
#include <EventData.h>

class PhysDist{
 public:
    virtual ~PhysDist() {}
    virtual PhysDist*   Clone() const = 0;

    virtual double operator()  (const std::vector<double>& vals_) const = 0;
    virtual double Probability (const EventData&) const = 0;
    
    virtual double Integral() const = 0;
    virtual void   Normalise()   = 0;

    virtual unsigned GetNDims() const = 0;    
};
#endif
