#ifndef __OXSX_HEAVISIDE__
#define __OXSX_HEAVISIDE__
#include <Function.h>

class Heaviside : public Function{
 public:
    enum Sidedness{MAXIMUM, MINIMUM, IGNORE};
    Heaviside(unsigned nDims_); // assume all ignored
    void AddConstraint(unsigned dim_, double pos_, Sidedness side_);

    double operator()(const std::vector<double>& vals_) const;

 private:
    std::vector<double>    fStepPosition;
    std::vector<Sidedness> fSidedness;
};
#endif
