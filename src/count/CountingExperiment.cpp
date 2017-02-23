#include <CountingExperiment.h>
#include <Event.h>
#include <DataSet.h>
#include <Formatter.hpp>
#include <EventSystematic.h>
#include <Histogram.h>
#include <iostream>
#include <cmath>

void
CountingExperiment::CountData(DataSet* testData_){
    int dataCount = 0;
    CutLog cutLog(fCuts.GetCutNames());
    for(size_t i = 0; i < testData_-> GetNEntries(); i++){
        Event transformed = fSystematics.ApplySystematics(testData_ -> GetEntry(i));
        if(fCuts.PassesCuts(transformed, cutLog))
            dataCount++;
    }    
    fResult.SetObservedCounts(dataCount);
    fResult.SetDataLog(cutLog);
}

double 
CountingExperiment::CountIteration(bool saveToResult_){
    double totalCounts = 0;
    // loop over all the background types
    for(size_t i = 0; i < fBackgroundDataSets.size(); i++){
        std::cout << fBackgroundNames.at(i) << std::endl;
        DataSet* dataSet = fBackgroundDataSets.at(i);
        int eventsPassed = 0;
        CutLog cutLog(fCuts.GetCutNames());

        // loop over events
        for(size_t j = 0; j < dataSet -> GetNEntries(); j++){
            Event transformed = fSystematics.ApplySystematics(dataSet->GetEntry(j));
            if(fCuts.PassesCuts(transformed, cutLog))
                eventsPassed++;
        }
        double counts = (eventsPassed * fBackgroundNorms.at(i) / dataSet->GetNEntries());
        totalCounts += counts;
        // MC statistics introduces a systematic error
        if(saveToResult_){
            double error = sqrt(eventsPassed) * fBackgroundNorms.at(i)/dataSet->GetNEntries();
            fResult.AddBackground(counts, fBackgroundNames.at(i), error, cutLog);
        }
    }
    return totalCounts;
}

void
CountingExperiment::CountBackgrounds(){
    CountIteration(true);
}

void 
CountingExperiment::CountAndSampleSystematics(int nrep_, Histogram& toFill_){
    if(toFill_.GetNDims() != 1)
        throw DimensionError("CountingExperiment::CountAndSampleSystematics", 1, toFill_.GetNDims(),
                             " histogram is filled with sampled background rates - must be 1D!");
    if(nrep_ <= 0)
        throw ValueError(Formatter() << "CountingExperiment::CountAndSampleSystematics "<< " nreps must be > 0");

    for(int i = 0; i < nrep_; i++){
        SetSystematicParams(fSampler.Sample());
        toFill_.Fill(CountIteration(false));
    }
    
    fResult.SetSampleHist(toFill_);
}


void 
CountingExperiment::CountSignal(){
    int signalCount = 0;
    CutLog cutLog = (fCuts.GetCutNames());
    for(size_t i = 0; i < fSignalDataSet -> GetNEntries(); i++){
        Event transformed = fSystematics.ApplySystematics(fSignalDataSet -> GetEntry(i));
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
CountingExperiment::AddSystematic(EventSystematic* sys_){
    fSystematics.Add(sys_);
    fCompManager.AddComponent(sys_);
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
                                                                          
void 
CountingExperiment::AddConstraint(PDF* pdf_, const std::string& paramName_){
    fSampler.AddParameter(pdf_, paramName_);
}
void 
CountingExperiment::AddConstraint(PDF* pdf_, const std::vector<std::string>& paramNames_){
    fSampler.AddCorrelatedSet(pdf_, paramNames_);    
}

void 
CountingExperiment::SetSystematicParams(const ParamMap& params_){
    for(ParamMap::const_iterator it = params_.begin(); it != params_.end(); ++it){
        fCompManager.SetParameter(it->first, it->second);
    }
}
