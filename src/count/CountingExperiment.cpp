#include <CountingExperiment.h>
#include <EventData.h>
#include <DataSet.h>
#include <iostream>

void
CountingExperiment::CountData(DataSet* testData_){
    fDataCount = 0;
    for(size_t i = 0; i < testData_-> GetNEntries(); i++){
        EventData transformed = fSystematics.ApplySystematics(testData_ -> GetEntry(i));
        if(fCuts.PassesCuts(transformed))
            fDataCount++;
    }
}


void
CountingExperiment::CountBackgrounds(){
    fBackgroundCount = 0;
    // loop over all the background types
    for(size_t i = 0; i < fBackgroundDataSets.size(); i++){
        DataSet* dataSet = fBackgroundDataSets.at(i);
        int eventsPassed = 0;

        // loop over events
        for(size_t j = 0; j < dataSet -> GetNEntries(); j++){
            EventData transformed = fSystematics.ApplySystematics(dataSet->GetEntry(j));
            if(fCuts.PassesCuts(transformed))
                eventsPassed++;            
        }
        fBackgroundCount += (eventsPassed * fBackgroundNorms.at(i) / dataSet->GetNEntries());
    }
}

double
CountingExperiment::GetBackgroundCount() const{
    return fBackgroundCount;
}

int 
CountingExperiment::GetDataCount() const{
    return fDataCount;
}

void
CountingExperiment::AddCut(const Cut& c_){
    fCuts.AddCut(c_);
}

void
CountingExperiment::AddSystematic(EventSystematic* sys_){
    fSystematics.Add(sys_);
}

void 
CountingExperiment::AddBackground(DataSet* mcData_, double rate_){
    fBackgroundDataSets.push_back(mcData_);
    fBackgroundNorms.push_back(rate_);
}

