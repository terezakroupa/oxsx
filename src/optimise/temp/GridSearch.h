#ifndef __GRID_SEARCH__
#define __GRID_SEARCH__
#include "Optimiser.h"
#include <vector>
#include <TTree.h>

struct Stepper{
    double min;
    double step;
    double max;
};

class GridSearch : public Optimiser{
 public:
    GridSearch();
    virtual void Optimise();

 private:
    std::vector<Stepper> fRateSteps;
    std::vector<Stepper> fSystematicSteps;

    std::vector<double>  fCurrentRates;
    std::vector<double>  fCurrentSystematics;

    double fMaxVal;
    bool   IncrementSystematic(size_t index_); // triggers recalculation of pdfs
    bool   IncrementRate(size_t index_);
};
#endif
