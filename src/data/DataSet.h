/******************************************************************/
/* Abstract base for a class that hands out data from some source */
/******************************************************************/
#ifndef __OXSX_DATA_SET__
#define __OXSX_DATA_SET__
#include <stddef.h>

class EventData;
class DataSet{
 public:
    DataSet() : fNEntries(0){}
    virtual EventData GetEntry(size_t iEvent_) = 0;
    virtual ~DataSet() {}
    virtual unsigned GetNEntries() const {return fNEntries;}
    
 protected:
    unsigned fNVar;
    unsigned fNEntries;
    

};

#endif
