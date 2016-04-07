#ifndef __OXSX_FUNCTION__
#define __OXSX_FUNCTION__
#include <FitComponent.h>
#include <vector>

class Function : public FitComponent{
 public:
    Function() : fNDims(0) {}
    virtual ~Function() {}
    virtual Function* Clone() const = 0;

    virtual double operator()(const std::vector<double>& vals_) const = 0;
    unsigned GetNDims() const;    
 protected:
    void SetNDims(unsigned nDims_);

 private:
    unsigned fNDims;
};
#endif
