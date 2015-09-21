/**************************************************************/
/* ABC for a data set from any origin, hands out data to oxsx */
/**************************************************************/
#ifndef __DATAHANDLE__
#define __DATAHANDLE__
#include <stddef.h>

class EventData;
class DataHandle{
 public:
    DataHandle() : fNEntries(0){}
    virtual EventData GetEntry(size_t iEvent_) = 0;
    virtual ~DataHandle() {}
    virtual unsigned GetNEntries() const {return fNEntries;}
    
 protected:
    unsigned fNVar;
    unsigned fNEntries;
    

};

#endif
