#ifndef __OXSX_FIT_COMPONENT__
#define __OXSX_FIT_COMPONENT__
#include <vector>
#include <string>

class FitComponent{
 public:
    void                     SetParameterValues(const std::vector<double>& vals_);
    std::vector<double>      GetParameterValues() const;
    std::vector<std::string> GetParameterNames() const;
    int                      GetParameterCount() const;

    virtual void MakeFittable() = 0;
 protected:
    void         Empty();   
    void         AddAsParameter(double*, const std::string&);
    void         DelegateFor(FitComponent*); // should only be used for objects owned by this one!
    void         SetParameterNames(const std::vector<std::string>& names_);

 private:
    size_t fNParams;
    std::vector<std::string> fParamNames;
    std::vector<double*>     fParamPtrs;
};
#endif
