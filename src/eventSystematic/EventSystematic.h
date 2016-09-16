#ifndef __OXSX_EVENT_SYSTEMATIC__
#define __OXSX_EVENT_SYSTEMATIC__
#include <DataRepresentation.h>
#include <FitComponent.h>
#include <vector>

class EventData;
class EventSystematic : public FitComponent{
 public:
    virtual EventData operator()(const EventData&) = 0;

    void       SetDataRep(const DataRepresentation&);
    DataRepresentation GetDataRep() const;
    
 protected:   
    DataRepresentation  fDataRep;
};
#endif
