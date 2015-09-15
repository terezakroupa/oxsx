#include <Evaluator.h>

void 
Evaluator::SetParams(const std::vector<double>& params_){
    fNormalisations.insert(fNormalisations.begin(), 
                                params_.begin(), params_.begin() + fNpdfs);
    fSystematicParams.insert(fSystematicParams.begin(), params_.begin() + fNpdfs, params_.end());
}


