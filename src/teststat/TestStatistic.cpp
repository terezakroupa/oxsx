#include <TestStatistic.h>

void 
TestStatistic::SetParams(const std::vector<double>& params_){
    fNormalisations.insert(fNormalisations.begin(), 
                                params_.begin(), params_.begin() + fNpdfs);
    fSystematicParams.insert(fSystematicParams.begin(), params_.begin() + fNpdfs, params_.end());
}


void 
TestStatistic::SetDataHandle(DataHandle* handle_){
    fDataHandle = handle_;
}

DataHandle*
TestStatistic::GetDataHandle() const{
    return fDataHandle;
}
