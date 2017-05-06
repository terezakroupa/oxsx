#include <Ensemble.h>
#include <TestStatistic.h>
#include <Exceptions.h>
#include <Optimiser.h>
#include <FitResult.h>
#include <ContainerTools.hpp>
void
Ensemble::RunPseudoExperiment(TestStatistic* stat_){
    if(!fNParams){
        fNParams = stat_->GetParameterCount();

    }
    
    if(fNParams != stat_->GetParameterCount())
        throw DimensionError("Ensemble", fNParams, stat_->GetParameterCount(), " the expected number of fit parameters was set the first time you called RunPseudoExperiment");

    const FitResult& fitResult = fOptimiser -> Optimise(stat_);
    const std::vector<double>& pointEstimate = GetValues(fitResult.GetBestFit());

}
