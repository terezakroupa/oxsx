/**************************************************************/
/* ABC for a data set from any origin, hands out data to oxsx */
/**************************************************************/
#ifndef __DATAHANDLE__
#define __DATAHANDLE__
#include <stddef.h>

class EventData;
class DataHandle{
 public:
    virtual EventData GetEntry(size_t iEvent_) = 0;
    virtual ~DataHandle() {}
    unsigned GetNEntries() const {return fNEntries;}
    
 private:
    unsigned fNVar;
    unsigned fNEntries;
    
    EventData Assemble(size_t iEvent_) const;
};

#endif
