#include <iostream>
#include <LogPosterior.h>
#include <PdfExceptions.h>
#include <SystematicExceptions.h>
#include <Function.h>
#include <cmath>

LogPosterior::LogPosterior(TestStatistic* testStat_, Function* prior_){
    fTestStat = testStat_;
    fPrior = prior_;
    fNpdfs = testStat_->GetNpdfs();
    fNsystematics = testStat_->GetNsystematics();
}

void
LogPosterior::SetDataSet(DataSet* dataSet_){
    fTestStat -> SetDataSet(dataSet_);
}

DataSet* 
LogPosterior::GetDataSet() const{
    return fTestStat -> GetDataSet();
}

void 
LogPosterior::SetParams(const std::vector<double>& params_){
    fParams = params_;
    try{
        fTestStat -> SetParams(params_);
    }
    catch(const DimensionError& e_){
        throw DimensionError(std::string("LogPosterior:: Underlying test stat rejected params set") + e_.what());
        
    }
    catch(const WrongNumberOfParameters& e_){
        throw WrongNumberOfParameters(std::string("LogPosterior:: Underlying test stat rejected params set") + e_.what());
        
    }
}


double
LogPosterior::Evaluate(){
    // avoid setting unphysical values by calculating the prior first, skip lh if prior is zero
    double val = fPrior -> operator()(fParams);
    if (val){
        return log(val) - fTestStat->Evaluate();
    }
    else{
        // fixme
        return -1e250;
    }

}


size_t
LogPosterior::GetNParams() const{
    return fPrior->GetNDims();
}
