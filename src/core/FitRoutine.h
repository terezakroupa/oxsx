/*************************************************************************************/
/* Controls a fit routine using an optimiser, evaluator, a set of PDFs and some data */
/*************************************************************************************/
#ifndef __FIT_ROUTINE__
#define __FIT_ROUTINE__
#include <PdfCollection.h>
#include <SystematicManager.h>

class Optimiser;
class Evaluator;
class Handle;
class TestSpace;
class FitResult;

class FitRoutine{
 public:
    FitRoutine() : fHandle(NULL), fOptimiser(NULL), fEvaluator(NULL) {}
    ~FitRoutine();

    void SetOptimiser(Optimiser*);
    void SetEvaluator(Evaluator*);
    void SetHandle(Handle*);
    
    FitResult Fit();
    
 private:
    Handle*            fHandle;
    Optimiser*         fOptimiser;
    Evaluator*         fEvaluator;
    PdfCollection      fPdfs;
    SystematicManager  fSystematicManager;
    
};
#endif
