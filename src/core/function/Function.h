#ifndef __OXSX_FUNCTION__
#define __OXSX_FUNCTION__
#include <vector>

class Function{
 public:
    Function() : fNDims(0) {}
    virtual ~Function() {}
    virtual Function* Clone() const = 0;

    virtual double operator()(const std::vector<double>& vals_) const = 0;

    double Call1D(double val) const;
    void SetNDims(unsigned);
    unsigned GetNDims() const;

    // Make functions tunable with a common interface
    void SetParameters(const std::vector<double>& params_);
    void SetParameter(size_t index_, double val_);

    std::vector<double> GetParameters()  const;
    double GetParameter(size_t index_)   const;

 protected:
    unsigned fNDims;
    std::vector<double> fParams;
};
#endif
