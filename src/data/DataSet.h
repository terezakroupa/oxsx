#ifndef __OXSX_DATA_SET__
#define __OXSX_DATA_SET__
#include <vector>
#include <DataHandle.h>
#include <EventData.h>

class DataSet : public DataHandle{
public:
    DataSet() : fData(new std::vector<EventData>()) {}
    ~DataSet();

    DataSet(const DataSet&); //deep copy
    DataSet operator=(const DataSet&);


    void AddEntry(const EventData&);
    EventData GetEntry(size_t eventIndex_);
    unsigned  GetNEntries() const;

private:
    std::vector<EventData>* fData;

};
#endif
