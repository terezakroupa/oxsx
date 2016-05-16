#ifndef __OXSX_INTERVAL__
#define __OXSX_INTERVAL__

class Histogram;
class Interval{
    virtual ~Interval() {}
    virtual double Evaluate(const Histogram&) = 0;
};
#endif
