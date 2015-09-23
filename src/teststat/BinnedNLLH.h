#ifndef __BinnedNLLH__
#define __BinnedNLLH__

#include <TestStatistic.h>
#include <BinnedPdfManager.h>
#include <SystematicManager.h>

class BinnedNLLH : public TestStatistic{
 public:
    BinnedNLLH():fCalculatedDataPdf(false) {}
    ~BinnedNLLH(){}

    double Evaluate();
    void   SetPdfManager(const BinnedPdfManager&);
    void   SetSystematicManager(const SystematicManager&);

    void   BinData();
 private:
    BinnedPdfManager  fPdfManager;
    SystematicManager fSystematicManager;  
    
    BinnedPdf fDataPdf;
    bool      fCalculatedDataPdf;
    
    
};
#endif
