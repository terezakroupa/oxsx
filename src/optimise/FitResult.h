/****************************************************/
/* Output of a fit routine, used for limit setting. */
/****************************************************/
#ifndef __OXSX_FIT_RESULT__
#define __OXSX_FIT_RESULT__
#include <vector>
class Histogram;
class FitResult{
 public:
    FitResult() : fStatSpace(NULL)  {}
    FitResult(const FitResult&); //deep copy
    FitResult operator=(const FitResult&); //deep copy

    ~FitResult(); // frees stat space

    void  SetBestFit(const std::vector<double>&);
    std::vector<double> GetBestFit() const;

    void SetStatSpace(Histogram*);
    Histogram* GetStatSpace() const; 

    void SetStatSample(const std::vector<std::vector<double> >&);
    std::vector<std::vector<double> > GetStatSample() const;

 private:
    std::vector<double>   fBestFit;
    std::vector<std::vector<double> > fStatSample;
    Histogram*            fStatSpace;
    
};
#endif

