#ifndef __OXSX_FIT_COMPONENT__
#define __OXSX_FIT_COMPONENT__
#include <FitParameter.h>
#include <vector>
#include <string>

class FitComponent{
 public:
    // Constructory things
    virtual ~FitComponent();
    FitComponent(){}
    FitComponent(const FitComponent&){} 
    // dont do anything, new object has its own params

    // Public interface
    void                     SetParameterValues(const std::vector<double>& vals_);
    std::vector<double>      GetParameterValues() const;
    std::vector<std::string> GetParameterNames() const;
    int                      GetParameterCount() const;

    // Set the object up as fittable
    virtual void MakeFittable() = 0;

 protected:
    void         Empty();   
    void         AddAsParameter(FitParameter*, const std::string&);


    template<typename Container> void  AddContainer(Container& cntr_, const std::string& sharedName_);
    void         SetParameterNames(const std::vector<std::string>& names_);

    // should only be used for objects owned by this one!
    void         DelegateFor(FitComponent*); 


 private:
    size_t fNParams;
    std::vector<std::string>       fParamNames;
    std::vector<FitParameter*>     fParamPtrs;
};

#include <FitComponent.hpp>
#endif
