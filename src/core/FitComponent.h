#ifndef __OXSX_FIT_COMPONENT__
#define __OXSX_FIT_COMPONENT__
#include <vector>
#include <string>

class FitComponent{
 public:
    virtual ~FitComponent() {}
    virtual void   MakeFittable() = 0;

    virtual std::vector<std::string> GetParameterNames() const = 0;
    virtual void SetParameterNames(const std::vector<std::string>&) = 0;

    virtual std::vector<double> GetParameters() const = 0;
    virtual void SetParameters(const std::vector<double>&) = 0;

    virtual void   SetParameter(const std::string& name_, double val) = 0;
    virtual double GetParameter(const std::string& name_) const = 0;

    virtual size_t GetParameterCount() const = 0;
};
#endif
