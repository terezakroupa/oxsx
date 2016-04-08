/********************************************************************/
/* A routine to calculate a binned chi squared test.                */
/* NOTE: this can only make sense if all pdfs have the same binning */
/********************************************************************/

#ifndef __OXSX_CHI_SQUARED__
#define __OXSX_CHI_SQUARED__
#include <SystematicManager.h>
#include <BinnedPdfManager.h>
#include <TestStatistic.h>

//FIXME::Enforce equal binning on the pdfs
class ChiSquare : public TestStatistic{
 public:
    ChiSquare() : fCalculatedDataPdf(false) {}
    ~ChiSquare();

    double Evaluate();

    // Register the relevant fit components
    void RegisterFitComponents();

 private:
    bool              fCalculatedDataPdf;
    BinnedPdf         fDataPdf;
    void              BinData();

    BinnedPdfManager  fPdfManager;
    SystematicManager fSystematicManager;
};
#endif
