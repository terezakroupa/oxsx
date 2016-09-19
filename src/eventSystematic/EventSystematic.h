#ifndef __OXSX_EVENT_SYSTEMATIC__
#define __OXSX_EVENT_SYSTEMATIC__
#include <DataRepresentation.h>
#include <FitComponent.h>
#include <vector>

class Event;
class EventSystematic : public FitComponent{
 public:
    virtual Event operator()(const Event&) = 0;

    void       SetDataRep(const DataRepresentation&);
    DataRepresentation GetDataRep() const;
    
 protected:   
    DataRepresentation  fDataRep;
};
#endif
