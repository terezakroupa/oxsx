/******************************************************************/
/* Abstract base for a class that hands out data from some source */
/******************************************************************/
#ifndef __OXSX_DATA_SET__
#define __OXSX_DATA_SET__
#include <stddef.h>
#include <vector>
#include <string>

class DataRepresentation;
class EventData;
class DataSet{
 public:
    DataSet() : fNEntries(0), fNObservables(0){}
    virtual EventData GetEntry(size_t iEvent_) const = 0;
    virtual ~DataSet() {}

    virtual unsigned GetNEntries() const {return fNEntries;}
    virtual unsigned GetNObservables() const {return fNObservables;}

    virtual std::vector<std::string> GetObservableNames() const = 0;
    DataRepresentation MakeDataRep(const std::vector<std::string> observableNames_) const;

 protected:
    unsigned fNObservables;
    unsigned fNEntries;
    

};

#endif
