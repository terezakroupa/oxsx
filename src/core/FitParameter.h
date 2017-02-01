#ifndef __OXSX_FIT_PARAMETER__
#define __OXSX_FIT_PARAMETER__
#include <string>

class FitParameter{
 public:
    virtual ~FitParameter() {}
    virtual double Get() const = 0;
    virtual void   Set(double) = 0;
    
    virtual std::string GetName() const = 0;
    virtual void SetName(const std::string&) = 0;
};

#endif
