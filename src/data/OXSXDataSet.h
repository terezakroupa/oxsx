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
#include <string>
class OXSXDataSet : public DataSet{
public:
    OXSXDataSet() : fData(new std::vector<EventData>()) {} //initialises DataSet::fnObservables to 0
    ~OXSXDataSet(); // frees fData

    OXSXDataSet(const OXSXDataSet&); //deep copy
    OXSXDataSet operator=(const OXSXDataSet&);

    void      AddEntry(const EventData&);
    EventData GetEntry(size_t eventIndex_) const;
    unsigned  GetNEntries() const;

    void SetObservableNames(const std::vector<std::string>& names_);
    std::vector<std::string> GetObservableNames() const;
    
    // concatenate
    OXSXDataSet operator+ (const OXSXDataSet& other_);

private:
    std::vector<EventData>* fData;
    std::vector<std::string> fObservableNames;
};
#endif
