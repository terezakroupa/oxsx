#ifndef __OXSX_SPECTRAL_FIT_PDF__
#define __OXSX_SPECTRAL_FIT_PDF__
#include <BinnedPhysDist.h>
#include <FitComponent.h>
#include <ParameterManager.h>

class SpectralFitDist : public BinnedPhysDist, public FitComponent{
 public:
    SpectralFitDist(const AxisCollection& axes_) : BinnedPhysDist(axes_) {}

    // Make this fittable with each bin content adjustable
    void MakeFittable() {}
    std::vector<std::string> GetParameterNames() const;
    std::vector<double> GetParameters() const;
    size_t GetParameterCount() const;
    void   SetParameters(const std::vector<double>&);

};
#endif
