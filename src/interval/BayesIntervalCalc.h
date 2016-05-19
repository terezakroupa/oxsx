#ifndef __OXSX_BAYESINTERVALCALC__
#define __OXSX_BAYESINTERVALCALC__
#include <Histogram.h>

class BayesIntervalCalc{
 public:
    static double UpperBound(Histogram lh_, double cl_); // needs to be a 1D histogram
    
};
#endif
