/*************************************************************************************/
/* Controls a fit routine using an optimiser, evaluator, a set of PDFs and some data */
/*************************************************************************************/
#ifndef __FIT_ROUTINE__
#define __FIT_ROUTINE__

class Optimiser;
class Evaluator;
class Handle;

class FitRoutine{
 public:
    FitRoutine();
    ~FitRoutine();

 private:
    Handle*    fHandle;
    Optimiser* fOptimiser;
    Evaluator* fEvaluator;
    
};
#endif
