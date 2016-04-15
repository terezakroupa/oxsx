#ifndef __OXSX_SPECTRAL_FIT_PDF__
#define __OXSX_SPECTRAL_FIT_PDF__
#include <BinnedPdf.h>

class SpectralFitPdf : public BinnedPdf, public FitComponent{
 public:
    SpectralFitPdf(const AxisCollection& axes_) : BinnedPdf(axes_) {}
    void MakeFittable();
};
#endif
