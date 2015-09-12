/****************************************/
/* Abstract base class for an optimiser */
/****************************************/
#ifndef __OPTIMISER__
#define __OPTIMISER__
#include <vector>

class Evaluator;
class FitResult;

class Optimiser{
 public:
    Optimiser() : pEvaluator(NULL), pPdfs(NULL) {}
    ~Optimiser();
    
    FitResult Optimise();
    
 private:
    Evaluator* pEvaluator; 
    std::vector<double> fBestRates;
    std::vector<double> fBestSystematics;

    bool fHasConverged;
};
#endif
