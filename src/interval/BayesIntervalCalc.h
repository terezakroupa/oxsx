#ifndef __OXSX_HISTOGRAM__
#define __OXSX_HISTOGRAM__
#include <Histogram.h>

class BayesIntervalCalc{
 public:
    static double LHLowerBound(const Histogram& lh_, double cl_); // needs to be a 1D histogram
    
};
#endif
