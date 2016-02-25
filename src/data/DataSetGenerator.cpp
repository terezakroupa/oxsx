#include <DataSetGenerator.h>
#include <DataSet.h>
#include <OXSXDataSet.h>
#include <DataExceptions.h>
#include <math.h>
#include <EventData.h>
#include <stdlib.h>
#include <Rand.h>

void
DataSetGenerator::SetDataSets(const std::vector<DataSet*> sets_){
    fDataSets = sets_;
}

void
DataSetGenerator::SetExpectedRates(const std::vector<double>& rates_){
    fExpectedRates = rates_;
    fSelectedEvents.clear();
    fSelectedEvents.resize(rates_.size());
}

OXSXDataSet
DataSetGenerator::ExpectedRatesDataSet(){
    if(fExpectedRates.size() != fDataSets.size())
        throw DataException("Can't generate fake data: need one rate exactly for each data set");

    OXSXDataSet dataSet;
    for(size_t i = 0; i < fDataSets.size(); i++){
        unsigned expectedCounts = round(fExpectedRates.at(i));

        for(unsigned j = 0; j < expectedCounts;){
            EventData event_ = RandomEvent(i);
            
            // Add event to new data set if it passes cut
            if (fCuts.PassesCuts(event_))
                dataSet.AddEntry(event_);
                j++;
            }
        }
    
    return dataSet;
}

OXSXDataSet
DataSetGenerator::PoissonFluctuatedDataSet(){
    if(fExpectedRates.size() != fDataSets.size())
        throw DataException("Can't generate fake data: need one rate exactly for each data set");

    OXSXDataSet dataSet;
    for(size_t i = 0; i < fDataSets.size(); i++){
        int counts = Rand::Poisson(fExpectedRates.at(i));

        for(unsigned j = 0; j < counts;){
            EventData event_ = RandomEvent(i);
            
            // check it passes the cuts                            
            if (fCuts.PassesCuts(event_)){
                dataSet.AddEntry(event_);
                j++;
            }
        }
    }
        
    return dataSet;
}


OXSXDataSet
DataSetGenerator::AllValidEvents(){
    OXSXDataSet dataSet;
    for(size_t i = 0; i < fDataSets.size(); i++){
        for(unsigned j = 0; j < fDataSets.at(i) -> GetNEntries(); j++){
            EventData event_ = fDataSets.at(i)->GetEntry(j);
            if (fCuts.PassesCuts(event_))
                dataSet.AddEntry(event_);
            
        } // events
    } // data sets
    return dataSet;
}


EventData
DataSetGenerator::RandomEvent(size_t handleIndex_){
    if (fSelectedEvents.size() == fDataSets.at(handleIndex_)->GetNEntries() && !fBootstrap){
        throw DataException("DataSetGenerator::Ran out of events!");
    }

    bool uniqueEvent = false;
    unsigned eventNum;

    const std::vector<size_t>& selectedEvents = fSelectedEvents.at(handleIndex_);
    while(!uniqueEvent){
        eventNum = Rand::Shoot(fDataSets.at(handleIndex_)->GetNEntries());
        if (std::find(selectedEvents.begin(), selectedEvents.end(), eventNum) == selectedEvents.end())
            uniqueEvent = true;
    }
    
    if (!fBootstrap)
        fSelectedEvents[handleIndex_].push_back(eventNum);
    return fDataSets.at(handleIndex_)->GetEntry(eventNum);
}

void
DataSetGenerator::AddDataSet(DataSet* data_, double rate_){
    fDataSets.push_back(data_);
    fExpectedRates.push_back(rate_);
    fSelectedEvents.push_back(std::vector<size_t>());
}

void
DataSetGenerator::SetCuts(const CutCollection& cuts_){
    fCuts = cuts_;
}

void
DataSetGenerator::AddCut(const Cut& cut_){
    fCuts.AddCut(cut_);
}

bool
DataSetGenerator::GetBootstrap() const{
    return fBootstrap;
}

void
DataSetGenerator::SetBootstrap(bool b_){
    fBootstrap = b_;
}

void 
DataSetGenerator::Reset(){
    for(size_t i = 0; i < fExpectedRates.size(); i++)
        fSelectedEvents[i].clear();
}

void 
DataSetGenerator::ClearDataSets(){
    fExpectedRates.clear();
    fSelectedEvents.clear();
    fDataSets.clear();
}
