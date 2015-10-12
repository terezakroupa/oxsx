#include <iostream>
#include <Posterior.h>
#include <PdfExceptions.h>
#include <SystematicExceptions.h>
#include <Function.h>
#include <cmath>

Posterior::Posterior(TestStatistic* testStat_, Function* prior_){
    fTestStat = testStat_;
    fPrior = prior_;
    fNpdfs = testStat_->GetNpdfs();
    fNsystematics = testStat_->GetNsystematics();
}

void
Posterior::SetDataSet(DataSet* dataSet_){
    fTestStat -> SetDataSet(dataSet_);
}

DataSet* 
Posterior::GetDataSet() const{
    return fTestStat -> GetDataSet();
}

void 
Posterior::SetParams(const std::vector<double>& params_){
    fParams = params_;
    try{
        fTestStat -> SetParams(params_);
    }
    catch(const DimensionError& e_){
        throw DimensionError(std::string("Posterior:: Underlying test stat rejected params set") + e_.what());
        
    }
    catch(const WrongNumberOfParameters& e_){
        throw WrongNumberOfParameters(std::string("Posterior:: Underlying test stat rejected params set") + e_.what());
        
    }
}


double
Posterior::Evaluate(){
    // avoid setting unphysical values by calculating the prior first, skip lh if prior is zero
    double val = fPrior -> operator()(fParams);
    if (val){
        val *= exp(-1 * fTestStat -> Evaluate());
    }
    return val;
}


size_t
Posterior::GetNParams() const{
    return fPrior->GetNDims();
}
