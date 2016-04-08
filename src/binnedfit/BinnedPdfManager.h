/***************************************************************************************************/
/* A collection of BinnedPDFs with normalisations for calculating the probability of a given obs   */
/* given some rates and some pdfs                                                                  */
/***************************************************************************************************/
#ifndef __BINNED_PDF_MANAGER__
#define __BINNED_PDF_MANAGER__
#include <vector>
#include <BinnedPdf.h>
#include <BinnedPdfShrinker.h>
#include <FitComponent.h>

class EventData;
class SystematicManager;

class BinnedPdfManager : public FitComponent{
 public:
     BinnedPdfManager() : fNPdfs(0) {}
    ~BinnedPdfManager(){}

    void   AddPdf(const BinnedPdf&);
    void   AddPdfs(const std::vector<BinnedPdf>&);

    double Probability(const EventData&) const;
    double BinProbability(size_t) const;
    
    const std::vector<double>& GetNormalisations() const;
    void SetNormalisations(const std::vector<double>& normalisations_);

    void ApplySystematics(const SystematicManager& sysMan_);
    void ApplyShrink(const BinnedPdfShrinker&);

    const BinnedPdf& GetOriginalPdf(size_t index_) const;
    unsigned GetNPdfs() const;
    size_t   GetNDims() const;
    

    // Make a fittable component - i.e. rescale the binned pdfs inside to fit
    void MakeFittable();

 private:
    std::vector<BinnedPdf> fOriginalPdfs;
    std::vector<BinnedPdf> fWorkingPdfs;
    std::vector<double>    fNormalisations;
    int                    fNPdfs;
    //    std::vector<double>    fCachedParams;
    size_t fNDims;
};
#endif
