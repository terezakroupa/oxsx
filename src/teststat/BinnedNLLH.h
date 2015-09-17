#ifndef __BinnedNLLH__
#define __BinnedNLLH__

#include <TestStatistic.h>
#include <BinnedPdfManager.h>
#include <SystematicManager.h>

class BinnedNLLH : public TestStatistic{
 public:
    BinnedNLLH() {}
    ~BinnedNLLH(){}

    double Evaluate();
    void   SetPdfManager(const BinnedPdfManager&);
    void   SetSystematicManager(const SystematicManager&);


 private:
    BinnedPdfManager  fPdfManager;
    SystematicManager fSystematicManager;  
    
    void      BinData();
    BinnedPdf fDataPdf;
    bool      fCalculatedDataPdf;
    
    
};
#endif
