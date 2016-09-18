/***************************************************************************************************/
/* A collection of BinnedPDFs with normalisations for calculating the probability of a given obs   */
/* given some rates and some pdfs                                                                  */
/***************************************************************************************************/
#ifndef __OXSX_BINNEDPHYSDISTMAN__
#define __OXSX_BINNEDPHYSDISTMAN__
#include <BinnedPhysDist.h>
#include <BinnedPhysDistShrink.h>
#include <FitComponent.h>
#include <ParameterManager.h>
#include <vector>

class EventData;
class SystematicManager;

class BinnedPhysDistMan : public FitComponent{
 public:
    BinnedPhysDistMan() : fNPdfs(0) {}

    void   AddPdf(const BinnedPhysDist&);
    void   AddPdfs(const std::vector<BinnedPhysDist>&);

    double Probability(const EventData&) const;
    double BinProbability(size_t) const;
    
    const std::vector<double>& GetNormalisations() const;
    void SetNormalisations(const std::vector<double>& normalisations_);

    void ApplySystematics(const SystematicManager& sysMan_);
    void ApplyShrink(const BinnedPhysDistShrink&);

    const BinnedPhysDist& GetOriginalPdf(size_t index_) const;
    unsigned GetNPdfs() const;
    size_t   GetNDims() const;
    

    // Make a fittable component - i.e. rescale the binned pdfs inside to fit
    void MakeFittable();
    std::vector<std::string> GetParameterNames() const;
    std::vector<double> GetParameters() const;
    size_t GetParameterCount() const;
    void SetParameters(const std::vector<double>&);

 private:
    ParameterManager       fParameterManager;
    std::vector<BinnedPhysDist> fOriginalPdfs;
    std::vector<BinnedPhysDist> fWorkingPdfs;
    std::vector<double>    fNormalisations;
    int                    fNPdfs;
    //    std::vector<double>    fCachedParams;
    size_t fNDims;
};
#endif
