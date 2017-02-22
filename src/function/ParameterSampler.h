#ifndef __OXSX_PARAMETER_SAMPLER__
#define __OXSX_PARAMETER_SAMPLER__
#include <ParameterManager.h>
#include <vector>
#include <map>

typedef std::map<std::string, double> ParamMap;

class PDF;
class ParameterSampler{
 public:
    ~ParameterSampler(); // deletes pdf
    void AddCorrelatedSet(PDF*, const std::vector<std::string>& correlatedParamNames_); // clones pdf
    ParamMap Sample() const;

 private:
    std::vector<std::vector<std::string> > fParamNames;
    std::vector<PDF*> fPdfs;
};
#endif
