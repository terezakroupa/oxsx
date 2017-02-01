#ifndef __OXSX_DOUBLE_POINTER__
#define __OXSX_DOUBLE_POINTER__
#include <FitParameter.h>
#include <string>

class DoubleParameter : public FitParameter{
 public:
 DoubleParameter(const std::string& nm_,  double& ptr_) : fPtr(ptr_), fName(nm_) {}
    double Get() const {return fPtr;}
    void   Set(double d_) {fPtr = d_;}
    
    std::string GetName() const {return fName;}
    void SetName(const std::string& nm_){fName = nm_;}

 private:
    double& fPtr;
    std::string fName;
};
#endif
