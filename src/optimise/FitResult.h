/****************************************************/
/* Output of a fit routine, used for limit setting. */
/****************************************************/
#ifndef __OXSX_FIT_RESULT__
#define __OXSX_FIT_RESULT__
#include <vector>
class BinnedPdf;
class FitResult{
 public:
    FitResult() : fStatSpace(NULL)  {}
    FitResult(const FitResult&); //deep copy
    FitResult operator=(const FitResult&); //deep copy

    ~FitResult(); // frees stat space

    void  SetBestFit(const std::vector<double>&);
    std::vector<double> GetBestFit() const;

    void SetStatSpace(BinnedPdf*);
    BinnedPdf* GetStatSpace() const; 

 private:
    std::vector<double>   fBestFit;
    BinnedPdf*            fStatSpace;
    // Correlation matrix
    
};
#endif

