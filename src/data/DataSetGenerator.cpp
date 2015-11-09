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
}

OXSXDataSet
DataSetGenerator::ExpectedRatesDataSet() const{
    if(fExpectedRates.size() != fDataSets.size())
        throw DataException("Can't generate fake data: need one rate exactly for each data set");

    OXSXDataSet dataSet;
    for(size_t i = 0; i < fDataSets.size(); i++){
        unsigned expectedCounts = round(fExpectedRates.at(i));

        for(unsigned j = 0; j < expectedCounts;){
            EventData event_ = RandomEvent(i);
            
            // check it passes the cuts
            bool passesCuts = true;
            for(size_t k = 0; k < fCuts.size(); k++)
                passesCuts = passesCuts && fCuts.at(k).PassesCut(event_);
                
            
            if (passesCuts){
                dataSet.AddEntry(event_);
                j++;
            }
        }
    }
        
    return dataSet;
}

OXSXDataSet
DataSetGenerator::PoissonFluctuatedDataSet() const{
    if(fExpectedRates.size() != fDataSets.size())
        throw DataException("Can't generate fake data: need one rate exactly for each data set");

    OXSXDataSet dataSet;
    for(size_t i = 0; i < fDataSets.size(); i++){
        int counts = Rand::Poisson(fExpectedRates.at(i));

        for(unsigned j = 0; j < counts;){
            EventData event_ = RandomEvent(i);
            
            // check it passes the cuts
            bool passesCuts = true;
            for(size_t k = 0; k < fCuts.size(); k++)
                passesCuts = passesCuts && fCuts.at(k).PassesCut(event_);
                
            
            if (passesCuts){
                dataSet.AddEntry(event_);
                j++;
            }
        }
    }
        
    return dataSet;
}
    


EventData
DataSetGenerator::RandomEvent(size_t handleIndex_) const{
    unsigned eventNum = Rand::Shoot(fDataSets.at(handleIndex_)->GetNEntries());
    return fDataSets.at(handleIndex_)->GetEntry(eventNum);
}

void
DataSetGenerator::AddDataSet(DataSet* data_, double rate_){
    fDataSets.push_back(data_);
    fExpectedRates.push_back(rate_);
}

void
DataSetGenerator::AddCut(const Cut& cut_){
    fCuts.push_back(cut_);
}

Cut
DataSetGenerator::GetCut(size_t index_) const{
    return fCuts.at(index_);
}

void
DataSetGenerator::SetCuts(const std::vector<Cut>& cuts_){
    fCuts = cuts_;
}

