#ifndef __GRID_SEARCH__
#define __GRID_SEARCH__
#include <Optimiser.h>
#include <vector>

class GridSearch : public Optimiser{
 public:
    GridSearch(Evaluator* eval_) : Optimiser(eval_){}
    virtual void Optimise();
    
    void SetMinima(const std::vector<double>&);
    void SetMaxima(const std::vector<double>&);

    std::vector<double> GetMinima() const;
    std::vector<double> GetMaxima() const;
        
 private:
    std::vector<double> fBestFit;
    std::vector<double> fParams;

    std::vector<double> fMinima;
    std::vector<double> fMaxima;
    std::vector<double> fStepSizes;
    bool Increment(size_t);
    double fMaxVal;
    
};
#endif
