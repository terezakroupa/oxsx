/***************************************************************************************************/
/* This class is responsible for shrinking pdfs to a subset of their normal range by truncating or */
/* rebinning into over/underflows. This is typically used to create a buffer around the fit        */
/* region. So that systematics can affect the boundary in a smooth physical way                    */
/***************************************************************************************************/

#ifndef __OXSX_BINNEDPDFSHRINKER__
#define __OXSX_BINNEDPDFSHRINKER__
#include <vector>
#include <BinnedPdf.h>

class BinnedPdfShrinker{
 public:
    BinnedPdfShrinker(unsigned nDims_);
    ~BinnedPdfShrinker(){}
    
    BinnedPdf ShrinkPdf(const BinnedPdf& pdf_) const;
    void SetLowerBuffer(size_t dimension_, unsigned nBins_);
    unsigned GetLowerBuffer(size_t dimension_) const;

    void SetUpperBuffer(size_t dimension_, unsigned nBins_);
    unsigned GetUpperBuffer(size_t dimension_) const;

    static PdfAxis ShrinkAxis(const PdfAxis&, const unsigned lowerBuff_, 
                              const unsigned upperBuff_);
    void SetUsingOverflows(bool b_);
    bool GetUsingOverflows() const;

    size_t GetNDims() const;

 private:
    BinnedPdfShrinker() {}
    std::vector<unsigned> fLowerBinBuffers; // initalised to zero in const.
    std::vector<unsigned> fUpperBinBuffers; // initalised to zero in const.
    size_t fNDims;
    bool fUsingOverflows;
};
#endif
