#ifndef __OXSX_FAKE_PDF_GENERATOR__
#define __OXSX_FAKE_PDF_GENERATOR__
#include <BinnedPhysDist.h>

class FakePdfGenerator{
 public:
    void SetPdfs(const std::vector<BinnedPhysDist>& pdfs_) {fPdfs = pdfs_;}
    std::vector<BinnedPhysDist> GetPdfs(const std::vector<BinnedPhysDist>& pdfs_) const {return fPdfs;}

    void SetRates(const std::vector<double> rates_) {fRates = rates_;}
    std::vector<double> GetRates() const {return fRates;}
    
    BinnedPhysDist ExpectedRatesPdf() const;
    BinnedPhysDist PoissonFluctuatedPdf() const;

 private:
    std::vector<BinnedPhysDist> fPdfs;
    std::vector<double>    fRates;
    size_t RandomBin(size_t pdfIndex_) const;
};
#endif
