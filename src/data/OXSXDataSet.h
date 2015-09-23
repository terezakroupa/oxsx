/**********************************************************************************************/
/* OXSX own data object, can be written and read from HTF5 compressed files                   */
/* Simply a wrapper on a vector of EventData objects, dynamically allocated to stop the stack */
/* filling up.                                                                                */
/**********************************************************************************************/

#ifndef __OXSX_OXSX_DATA_SET__
#define __OXSX_OXSX_DATA_SET__
#include <vector>
#include <DataSet.h>
#include <EventData.h>

class OXSXDataSet : public DataSet{
public:
    OXSXDataSet() : fData(new std::vector<EventData>()) {}
    ~OXSXDataSet(); // frees fData

    OXSXDataSet(const OXSXDataSet&); //deep copy
    OXSXDataSet operator=(const OXSXDataSet&);

    void AddEntry(const EventData&);
    EventData GetEntry(size_t eventIndex_);
    unsigned  GetNEntries() const;

private:
    std::vector<EventData>* fData;

};
#endif
