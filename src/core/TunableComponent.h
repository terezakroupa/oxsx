#ifndef __OXSX_TUNABLE_COMPONENT__
#define __OXSX_TUNABLE_COMPONENT__
#include <string>
#include <vector>

class TunableComponent{
 public:
    void SetParameters(const std::vector<double>& vals_);
    std::vector<double> GetParameters() const;
    void   SetParameter(size_t index_, double val_);
    double GetParamter() const;
    
    int GetParameterCount() const;

 protected:
    void SetParamPtr();
    void Empty();
    void AddAsParameter(double*, const std::string&);
   
 private:
    size_t fNParams;
    std::vector<double*>     fParamPtrs;
    std::vector<std::string> fParamNames;
};
#endif
