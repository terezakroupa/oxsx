#include <DataSetGenerator.h>
#include <DataSet.h>
#include <OXSXDataSet.h>
#include <Exceptions.h>
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
}

OXSXDataSet
DataSetGenerator::ExpectedRatesDataSet() const{
    if(fExpectedRates.size() != fDataSets.size())
        throw LogicError("Can't generate fake data: need one rate exactly for each data set");

    if(!fDataSets.size())
        throw LogicError("Can't generate fake data: no input data sets");

    OXSXDataSet dataSet;
    dataSet.SetObservableNames(fDataSets.at(0)->GetObservableNames());

    for(size_t i = 0; i < fDataSets.size(); i++){
        int expectedCounts = round(fExpectedRates.at(i));
        std::vector<size_t> passingIndicies = EventsPassingCuts(i);

        for(unsigned j = 0; j < expectedCounts; j++)
            dataSet.AddEntry(RandomEventFromList(i, passingIndicies));
    }

    return dataSet;
}

OXSXDataSet
DataSetGenerator::PoissonFluctuatedDataSet() const{
    if(fExpectedRates.size() != fDataSets.size())
        throw LogicError("Can't generate fake data: need one rate exactly for each data set");
    if(!fDataSets.size())
      throw LogicError("Can't generate fake data: no input data sets");

    OXSXDataSet dataSet;
    dataSet.SetObservableNames(fDataSets.at(0)->GetObservableNames());
    for(size_t i = 0; i < fDataSets.size(); i++){
        int counts = Rand::Poisson(fExpectedRates.at(i));
        std::vector<size_t> passingIndicies = EventsPassingCuts(i);
        for(unsigned j = 0; j < counts; j++)
            dataSet.AddEntry(RandomEventFromList(i, passingIndicies));
    }

    return dataSet;
}


EventData
DataSetGenerator::RandomEvent(size_t handleIndex_) const{
    unsigned eventNum = Rand::Shoot(fDataSets.at(handleIndex_)->GetNEntries());
    return fDataSets.at(handleIndex_)->GetEntry(eventNum);
}

EventData
DataSetGenerator::RandomEventFromList(size_t handleIndex_,
                                      const std::vector<size_t>& nums_) const{
    unsigned eventNum = Rand::Shoot(nums_.size());
    return fDataSets.at(handleIndex_)->GetEntry(nums_.at(eventNum));
}

void
DataSetGenerator::AddDataSet(DataSet* data_, double rate_){
    fDataSets.push_back(data_);
    fExpectedRates.push_back(rate_);
}

void
DataSetGenerator::SetCuts(const CutCollection& cuts_){
    fCuts = cuts_;
}

std::vector<size_t>
DataSetGenerator::EventsPassingCuts(size_t handleIndex_) const{
    std::vector<size_t> passingIndicies;
    passingIndicies.reserve(fDataSets.at(handleIndex_) -> GetNEntries() /2);

    for(size_t i = 0; i < fDataSets.at(handleIndex_) -> GetNEntries(); i++){
        if(fCuts.PassesCuts(fDataSets.at(handleIndex_)->GetEntry(i)))
            passingIndicies.push_back(i);
    }
    return passingIndicies;
}
