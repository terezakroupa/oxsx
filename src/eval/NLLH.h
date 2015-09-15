#ifndef __NLLH__
#define __NLLH__

#include <Evaluator.h>
#include <PdfCollection.h>
#include <SystematicManager.h>

class NLLH : public Evaluator{
 public:
    NLLH();
    ~NLLH();

    double Evaluate();
    
 private:
    PdfCollection     fPdfCollection;
    SystematicManager fSystematicManager;
  
    
};
#endif
