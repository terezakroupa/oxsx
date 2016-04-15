#include <SpectralFitPdf.h>

void
SpectralFitPdf::MakeFittable(){
    EmptyParameters();
    DelegateFor(&fHistogram);
}
