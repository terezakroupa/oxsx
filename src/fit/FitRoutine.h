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
    Handle*            fHandle;    // responsible for data
    Optimiser*         fOptimiser; // responsible for optimisation
    Evaluator*         fEvaluator; // evaluates test stat from data and pdf
    PdfCollection      fPdfs;      // Gives probabilities of observations
    SystematicManager  fSystematicManager; // responsible for the systematics

    size_t fNPdfs;
    size_t fNSystematics;
    std::vector<double> fSystematicParams;
    std::vector<double> fNormalisationParams; 
    void SplitParams(const std::vector<double>& params_); //into systamatics and normalisations
       
};
#endif
