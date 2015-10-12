#include <TestStatistic.h>
#include <iostream>
#include <PdfExceptions.h>
#include <SystematicExceptions.h>

void 
TestStatistic::SetParams(const std::vector<double>& params_){
    fNormalisations.resize(0);
    fSystematicParams.resize(0);

    try{
        fNormalisations.insert(fNormalisations.begin(), 
                               params_.begin(), params_.begin() + fNpdfs);

        fSystematicParams.insert(fSystematicParams.begin(), params_.begin() + fNpdfs, params_.end());
    }

    catch(const DimensionError& e_){
        throw DimensionError(std::string("TestStatistic: Wrong number of norms") + e_.what());
    }
    catch(const WrongNumberOfParameters& e_){
        throw WrongNumberOfParameters(std::string("TestStatistic: Wrong number of systematic params sent in") + e_.what());
    }

}


void 
TestStatistic::SetDataSet(DataSet* dataSet_){
    fDataSet = dataSet_;
}

DataSet*
TestStatistic::GetDataSet() const{
    return fDataSet;
}

size_t 
TestStatistic::GetNsystematics() const{
    return fNsystematics;
}

size_t
TestStatistic::GetNpdfs() const{
    return fNpdfs;
}
