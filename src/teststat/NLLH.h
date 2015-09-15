#ifndef __NLLH__
#define __NLLH__

#include <TestStatistic.h>
#include <PdfManager.h>
#include <SystematicManager.h>

class NLLH : public TestStatistic{
 public:
    NLLH();
    ~NLLH();

    double Evaluate();
    
 private:
    PdfManager        fPdfManager;
    SystematicManager fSystematicManager;  
    
};
#endif
