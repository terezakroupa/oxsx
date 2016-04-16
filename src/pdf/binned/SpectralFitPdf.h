#ifndef __OXSX_SPECTRAL_FIT_PDF__
#define __OXSX_SPECTRAL_FIT_PDF__
#include <BinnedPdf.h>
#include <FitComponent.h>
#include <ParameterManager.h>

class SpectralFitPdf : public BinnedPdf, public FitComponent{
 public:
    SpectralFitPdf(const AxisCollection& axes_) : BinnedPdf(axes_) {}

    // Make this fittable with each bin content adjustable
    void MakeFittable() {}
    std::vector<std::string> GetParameterNames() const;
    std::vector<double> GetParameters() const;
    size_t GetParameterCount() const;
    void   SetParameters(const std::vector<double>&);

};
#endif
