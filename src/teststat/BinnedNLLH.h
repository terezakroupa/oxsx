#ifndef __BinnedNLLH__
#define __BinnedNLLH__

#include <TestStatistic.h>
#include <BinnedPdfManager.h>
#include <SystematicManager.h>

class BinnedNLLH : public TestStatistic{
 public:
    BinnedNLLH();
    ~BinnedNLLH();

    double Evaluate();
    
 private:
    BinnedPdfManager  fPdfManager;
    SystematicManager fSystematicManager;  
    
};
#endif
