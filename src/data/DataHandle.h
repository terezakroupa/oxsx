/**************************************************************/
/* ABC for a data set from any origin, hands out data to oxsx */
/**************************************************************/
#ifndef __DATAHANDLE__
#define __DATAHANDLE__
#include <stddef.h>

class DataHandler;
class DataHandle{
 public:
    virtual DataHandler GetEntry(size_t iEvent_) = 0;
    virtual ~DataHandle() {}
    unsigned GetNEntries() const {return fNEntries;}
    
 private:
    unsigned fNVar;
    unsigned fNEntries;
    
    DataHandler Assemble(size_t iEvent_) const;
};

#endif
