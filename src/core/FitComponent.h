#ifndef __OXSX_FIT_COMPONENT__
#define __OXSX_FIT_COMPONENT__
#include <FitParameter.h>
#include <vector>
#include <string>

class FitComponent{
 public:
    virtual ~FitComponent();

    void                     SetParameterValues(const std::vector<double>& vals_);
    std::vector<double>      GetParameterValues() const;
    std::vector<std::string> GetParameterNames() const;
    int                      GetParameterCount() const;

    virtual void MakeFittable() = 0;
 protected:
    void         Empty();   
    void         AddAsParameter(FitParameter*, const std::string&);
    void         DelegateFor(FitComponent*); // should only be used for objects owned by this one!
    void         SetParameterNames(const std::vector<std::string>& names_);

 private:
    size_t fNParams;
    std::vector<std::string>       fParamNames;
    std::vector<FitParameter*>     fParamPtrs;
};
#endif
