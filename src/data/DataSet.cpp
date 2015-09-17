#include <DataSet.h>
#include <EventData.h>
void
DataSet::AddEntry(const EventData& evData_){
    fData -> push_back(evData_);
    fEntryCount++;
}

EventData
DataSet::GetEntry(size_t eventIndex_){
    return fData -> at(eventIndex_);
}

unsigned
DataSet::GetNEntries() const{
    return fData -> size();
}

DataSet::~DataSet(){
    delete fData;
}

DataSet::DataSet(const DataSet& other_){
    fData = new std::vector<EventData>(*other_.fData);
}

DataSet
DataSet::operator=(const DataSet& other_){
    fData = new std::vector<EventData>(*other_.fData);
    return *this;
}
