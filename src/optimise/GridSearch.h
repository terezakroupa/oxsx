#ifndef __GRID_SEARCH__
#define __GRID_SEARCH__
#include <Optimiser.h>
#include <vector>
#include <FitResult.h>

class GridSearch : public Optimiser{
 public:
    GridSearch(TestStatistic* stat_) : Optimiser(stat_), fMaximising(false){}
    virtual FitResult Optimise();
    
    void SetMinima(const std::vector<double>&);
    void SetMaxima(const std::vector<double>&);
    void SetStepSizes(const std::vector<double>&);

    std::vector<double> GetMinima() const;
    std::vector<double> GetMaxima() const;
    std::vector<double> GetStepSizes()  const;
    
    FitResult GetFitResult() const;
    void SetMaximising(bool);
    bool GetMaximising() const;

 private:
    std::vector<double> fParams;
    FitResult           fFitResult;
    
    bool fMaximising;

    std::vector<double> fMinima;
    std::vector<double> fMaxima;
    std::vector<double> fStepSizes;
    bool Increment(size_t);
    double fMinVal;
    
};
#endif
