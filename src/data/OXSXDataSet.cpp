#include <OXSXDataSet.h>
#include <EventData.h>
#include <DataExceptions.h>

void
OXSXDataSet::AddEntry(const EventData& evData_){
    // fNObservables is zero at initialisation, after the first time it is set it shouldnt change
    if(!fNObservables)
        fNObservables = evData_.GetNDimensions();

    else if (fNObservables != evData_.GetNDimensions())
        throw DataException("OXSXDataSet::Event added to data set doesn't match existing dimensions");

    if(!evData_.GetNDimensions())
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
