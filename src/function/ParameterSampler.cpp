#include <ParameterSampler.h>
#include <PDF.h>
#include <FitParameter.h>
#include <Exceptions.h>

ParameterSampler::~ParameterSampler(){
    for(size_t i = 0; i < fPdfs.size(); i++)
        delete fPdfs[i];
}

void
ParameterSampler::AddCorrelatedSet(PDF* pdf_,
                                   const std::vector<std::string>& correlatedParamNames_){
    if (pdf_->GetNDims() != correlatedParamNames_.size()){
        throw DimensionError("ParameterSampler::Add", pdf_->GetNDims(), correlatedParamNames_.size(), 
                             "Expect one parameter for each dimension of PDF added");
    }
    
    // now copy
    fPdfs.push_back(dynamic_cast<PDF*>(pdf_->Clone()));
    fParamNames.push_back(correlatedParamNames_);
}

ParamMap
ParameterSampler::Sample() const{
    ParamMap params;

    std::vector<double> sample;
    std::vector<std::string> names;
    for(size_t i = 0; i < fPdfs.size(); i++){
        sample = fPdfs.at(i) -> Sample();
        names  = fParamNames.at(i);
        for(size_t j = 0; j < sample.size(); j++){
            params[names.at(j)] = sample.at(j);
        }
    }
    return params;
}
