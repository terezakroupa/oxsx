/***************************************************************************************************/~
/* A collection of BinnedPDFs with normalisations for calculating the probability of a given obs   */
/* given some rates and some pdfs                                                                  */
/***************************************************************************************************/
#ifndef __BINNED_PDF_MANAGER__
#define __BINNED_PDF_MANAGER__
#include <vector>
#include <BinnedPdf.h>

class EventData;
class Systematic;

class BinnedPdfManager{
 public:
    BinnedPdfManager() {}
    ~BinnedPdfManager();

    void   AddPdf(const BinnedPdf&);
    void   AddPdfs(const std::vector<BinnedPdf>&);

    double Probability(const EventData&) const;
    
    std::vector<double> GetNormalisations() const;
    void SetNormalisations(const std::vector<double>& normalisations_);
    void ApplySystematics(const std::vector<Systematic>&);

    const BinnedPdf& GetOriginalPdf(size_t index_) const;
    size_t GetNDims() const;

 private:
    std::vector<BinnedPdf> fOriginalPdfs;
    std::vector<BinnedPdf> fWorkingPdfs;
    std::vector<double>    fNormalisations;
    size_t fNDims;
};
#endif
