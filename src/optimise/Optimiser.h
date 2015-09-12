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
    Optimiser(Evaluator* ev_) : pEvaluator(ev_) {}
    virtual ~Optimiser();
    
    virtual bool Iterate() = 0;
    FitResult GetFitResult();
    
    const std::vector<double>& GetParams() const;
    void  SetTestValue(double);

 private:
    Evaluator* pEvaluator; 
    bool fHasConverged;
    std::vector<double> fParams;
    double fTestValue;
};
#endif
