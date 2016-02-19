/****************************************************/
/* Output of a fit routine, used for limit setting. */
/****************************************************/
#ifndef __OXSX_FIT_RESULT__
#define __OXSX_FIT_RESULT__
#include <cstdlib>
#include <vector>
class Histogram;
class FitResult{
 public:
    FitResult() : fStatSpace(NULL), fIsValid(true)  {}
    FitResult(const FitResult&); //deep copy
    FitResult operator=(const FitResult&); //deep copy

    ~FitResult(); // frees stat space

    void  SetBestFit(const std::vector<double>&);
    std::vector<double> GetBestFit() const;

    void SetStatSpace(const Histogram&);
    const Histogram& GetStatSpace() const; 

    void SetStatSample(const std::vector<std::vector<double> >&);
    const std::vector<std::vector<double> >& GetStatSample() const;
    
    void SetValid(bool b_);
    bool GetValid() const;

 private:
    std::vector<double>   fBestFit;
    std::vector<std::vector<double> > fStatSample;
    Histogram*            fStatSpace;
    bool fIsValid;
};
#endif

