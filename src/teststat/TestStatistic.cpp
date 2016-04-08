#include <TestStatistic.h>
#include <iostream>
#include <PdfExceptions.h>
#include <SystematicExceptions.h>
void 
TestStatistic::SetDataSet(DataSet* dataSet_){
    fDataSet = dataSet_;
}

DataSet*
TestStatistic::GetDataSet() const{
    return fDataSet;
}

void
TestStatistic::SetParameters(const std::vector<double>& params_){
    fComponentManager.Clear();
    RegisterFitComponents();   // derived classes implement this to choose fit components
    try{
        fComponentManager.SetParameters(params_);
    }
    catch(const ParameterError& ){
        throw ParameterError("TestStatistic passed wrong number of parameters!");
    }
}

int
TestStatistic::GetParameterCount() const{
    return fComponentManager.GetTotalParameterCount();
}

void
TestStatistic::AddFitComponent(FitComponent* comp_){
    fComponentManager.AddComponent(comp_);    
}
