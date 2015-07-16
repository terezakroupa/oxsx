/****************************************/
/* Abstract base class for an optimiser */
/****************************************/
#ifndef __OPTIMISER__
#define __OPTIMISER__
#include "../eval/Evaluator.h"
#include <vector>

class Optimiser{
 public:
    Optimiser();
    virtual ~Optimiser() {}
    virtual void Optimise() = 0;

    void SetEvaluator(Evaluator* evaluator_) {fEvaluator = evaluator_;}
    std::vector<double> GetBestRates() const {return fBestRates;}
    std::vector<double> GetBestSystematics() const {return fBestSystematics;}

 protected:
    Evaluator* fEvaluator;
    std::vector<double> fBestRates;
    std::vector<double> fBestSystematics;
};
#endif
