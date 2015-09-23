#include <OXSXDataset.h>
#include <EventData.h>
#include <DataExceptions.h>
void
OXSXDataSet::AddEntry(const EventData& evData_){
    fData -> push_back(evData_);
}

EventData
OXSXDataSet::GetEntry(size_t eventIndex_){
    try{
    return fData -> at(eventIndex_);
    }
    catch(std::out_of_range&){
        throw DataNotFoundError("");
    }
}

unsigned
OXSXDataSet::GetNEntries() const{
    return fData -> size();
}

OXSXDataSet::~OXSXDataSet(){
    delete fData;
}

OXSXDataSet::OXSXDataSet(const OXSXDataSet& other_){
    fData = new std::vector<EventData>(*other_.fData);
}

OXSXDataSet
OXSXDataSet::operator=(const OXSXDataSet& other_){
    fData = new std::vector<EventData>(*other_.fData);
    return *this;
}



