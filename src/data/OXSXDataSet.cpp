#include <OXSXDataSet.h>
#include <EventData.h>
#include <DataExceptions.h>
#include <iostream>
void
OXSXDataSet::AddEntry(const EventData& evData_){
    // fNObservables is zero at initialisation, after the first time it is set it shouldnt change
    if(!fNObservables)
        fNObservables = evData_.GetNObservables();

    else if (fNObservables != evData_.GetNObservables())
        throw DataException("OXSXDataSet::Event added to data set doesn't match existing dimensions");

    if(!evData_.GetNObservables())
        throw DataException("OXSXDataSet::Tried to add empty event to data set");

    fData -> push_back(evData_);
}

EventData
OXSXDataSet::GetEntry(size_t eventIndex_) const{
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

void
OXSXDataSet::SetObservableNames(const std::vector<std::string>& names_){
    fObservableNames = names_;
}

std::vector<std::string>
OXSXDataSet::GetObservableNames() const{
    return fObservableNames;
}


OXSXDataSet
OXSXDataSet::operator+ (const OXSXDataSet& other_){
    for(size_t i = 0; i < other_.GetNEntries(); i++)
        AddEntry(other_.GetEntry(i));
    
    return *this;
}

void
OXSXDataSet::Reserve(int i){
  fData->reserve(i);
}

unsigned
OXSXDataSet::GetNObservables() const{
    return fNObservables;
}
