#include <Evaluator.h>

void 
Evaluator::SetParams(const std::vector<double>& params_){
    fNormalisations.insert(fNormalisations.begin(), 
                                params_.begin(), params_.begin() + fNpdfs);
    fSystematicParams.insert(fSystematicParams.begin(), params_.begin() + fNpdfs, params_.end());
}


void 
Evaluator::SetDataHandle(Handle* handle_){
    fHandle = handle_;
}

Handle*
Evaluator::GetDataHandle() const{
    return fHandle;
}
