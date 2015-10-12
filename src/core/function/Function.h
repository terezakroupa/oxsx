#ifndef __OXSX_FUNCTION__
#define __OXSX_FUNCTION__
#include <vector>

class Function{
 public:
    Function() : fNDims(0) {}
    virtual double operator()(const std::vector<double>& vals_) const = 0;
    void SetNDims(unsigned);
    unsigned GetNDims() const;

 protected:
    unsigned fNDims;
};
#endif
