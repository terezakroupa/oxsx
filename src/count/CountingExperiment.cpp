#include <CountingExperiment.h>
#include <EventData.h>
#include <DataSet.h>
#include <Formatter.hpp>
#include <iostream>

void
CountingExperiment::CountData(DataSet* testData_){
    int dataCount = 0;
    CutLog cutLog = (fCuts.GetCutNames());
    for(size_t i = 0; i < testData_-> GetNEntries(); i++){
        EventData transformed = fSystematics.ApplySystematics(testData_ -> GetEntry(i));
        if(fCuts.PassesCuts(transformed, cutLog))
            dataCount++;
    }    
    fResult.SetObservedCounts(dataCount);
    fResult.SetDataLog(cutLog);
}

void
CountingExperiment::CountBackgrounds(){
    // loop over all the background types
    for(size_t i = 0; i < fBackgroundDataSets.size(); i++){
        DataSet* dataSet = fBackgroundDataSets.at(i);
        int eventsPassed = 0;
        CutLog cutLog(fCuts.GetCutNames());

        // loop over events
        for(size_t j = 0; j < dataSet -> GetNEntries(); j++){
            EventData transformed = fSystematics.ApplySystematics(dataSet->GetEntry(j));
            if(fCuts.PassesCuts(transformed, cutLog))
                eventsPassed++;
        }
        double counts = (eventsPassed * fBackgroundNorms.at(i) / dataSet->GetNEntries());
        fResult.AddBackground(counts, fBackgroundNames.at(i), cutLog);
    }
}

void 
CountingExperiment::CountSignal(){
    int signalCount = 0;
    CutLog cutLog = (fCuts.GetCutNames());
    for(size_t i = 0; i < fSignalDataSet -> GetNEntries(); i++){
        EventData transformed = fSystematics.ApplySystematics(fSignalDataSet -> GetEntry(i));
        if(fCuts.PassesCuts(transformed, cutLog))
            signalCount++;
    }    
    fResult.SetSignal(1. * signalCount/fSignalDataSet -> GetNEntries(), fSignalName, cutLog);
}

void
CountingExperiment::AddCut(const Cut& c_, const std::string& name_){
    fCuts.AddCut(c_, name_);
}

void
CountingExperiment::AddSystematic(EventSystematic* sys_, const std::string& name_){
    fSystematics.Add(sys_);
    fSystematicNames.push_back(name_);
}

void
CountingExperiment::AddBackground(DataSet* mcData_, double rate_, const std::string& name_){
    fBackgroundDataSets.push_back(mcData_);
    fBackgroundNorms.push_back(rate_);
    fBackgroundNames.push_back(name_);
}

const CountingResult&
CountingExperiment::GetCountingResult() const{
    return fResult;
}

void
CountingExperiment::SetSignal(DataSet* mcData_, const std::string& name_){
    fSignalDataSet = mcData_;
    fSignalName    = name_;
}
                                                                          
