#ifndef __OXSX_BAYES_INTERVALCALC__
#define __OXSX_BAYES_INTERVALCALC__
#include <Histogram.h>
#include <IntervalCalculator.h>

class BayesianUpperBound{
 public:
    BayesianUpperBound(double cl_) : fCl(cl_) {}
    double Evaluate(const Histogram& lh_); // needs to be a 1D histogram
    
 private:
    double fCl;
    
};
#endif
