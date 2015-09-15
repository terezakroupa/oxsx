/****************************************/
/* Abstract base class for an optimiser */
/****************************************/
#ifndef __OPTIMISER__
#define __OPTIMISER__
#include <vector>
#include <TestStatistic.h>

class FitResult;

class Optimiser{
 public:
    Optimiser(TestStatistic* evaluator_): pTestStatistic(evaluator_){}
    virtual ~Optimiser();

    virtual void Optimise() = 0;

 protected:
    TestStatistic* pTestStatistic;
};
#endif
