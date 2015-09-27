#ifndef __OXSX_RAND__
#define __OXSX_RAND__

class Rand{
 public:
    static double Uniform(double max_ = 1);
    static double Gaus(double mean_ = 0, double sigma_ = 1);
};
#endif
