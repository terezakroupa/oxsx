/**************************************************************/
/* ABC for a data set from any origin, hands out data to oxsx */
/**************************************************************/
#ifndef __HANDLE__
#define __HANDLE__
#include <stddef.h>

class DataHandler;
class Handle {
 public:
    virtual DataHandler GetEntry(size_t iEvent_) = 0;
    virtual ~Handle() {}
    unsigned GetNEntries() const {return fNEntries;}
    
 private:
    unsigned fNVar;
    unsigned fNEntries;
    
    DataHandler Assemble(size_t iEvent_) const;
};

#endif
