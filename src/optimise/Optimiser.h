/****************************************/
/* Abstract base class for an optimiser */
/****************************************/
#ifndef __OPTIMISER__
#define __OPTIMISER__
#include <vector>
#include <Evaluator.h>

class FitResult;

class Optimiser{
 public:
    Optimiser(Evaluator* evaluator_): pEvaluator(evaluator_){}
    virtual ~Optimiser();

    virtual void Optimise() = 0;

 protected:
    Evaluator* pEvaluator;
};
#endif
