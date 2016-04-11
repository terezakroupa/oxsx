#include <SpectralFitPdf.h>

void
SpectralFitPdf::MakeFittable(){
    DelegateFor(&fHistogram);
}
