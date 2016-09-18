/***************************************************************************************************/
/* This class is responsible for shrinking pdfs to a subset of their normal range by truncating or */
/* rebinning into over/underflows. This is typically used to create a buffer around the fit        */
/* region. So that systematics can affect the boundary in a smooth physical way                    */
/***************************************************************************************************/

#ifndef __OXSX_BINNEDPHYSDISTSHRINK__
#define __OXSX_BINNEDPHYSDISTSHRINK__
#include <BinnedPhysDist.h>
#include <map>
#include <utility> // std::pair


class BinnedPhysDistShrink{
 public:
    BinnedPhysDistShrink();
    ~BinnedPhysDistShrink(){}

    BinAxis ShrinkAxis(const BinAxis&, const unsigned lowerBuff_, 
                       const unsigned upperBuff_);    
    BinnedPhysDist ShrinkPdf(const BinnedPhysDist& pdf_) const;
    
    void SetBuffer(size_t dim_, unsigned lowerBuf_, unsigned upperBuf_);
    std::pair<unsigned, unsigned> GetBuffer(size_t dim_) const;
    
    std::map<size_t, std::pair<unsigned, unsigned> > GetBuffers() const;
     
    void SetUsingOverflows(bool b_);
    bool GetUsingOverflows() const;

 private:
    // Pairs of lower/upper buffer sizes in number of bins, keyed by diminension to shrink
    std::map<size_t, std::pair<unsigned, unsigned> > fBuffers; 
    bool fUsingOverflows; // true at initialisation
};
#endif
