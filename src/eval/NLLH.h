#ifndef __NLLH__
#define __NLLH__

#include <Evaluator.h>
#include <PdfManager.h>
#include <SystematicManager.h>

class NLLH : public Evaluator{
 public:
    NLLH();
    ~NLLH();

    double Evaluate();
    
 private:
    PdfManager        fPdfManager;
    SystematicManager fSystematicManager;  
    
};
#endif
