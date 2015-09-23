/**************************************************************/
/* Static Utility class for doing a variety of pdfconversions */
/**************************************************************/
#ifndef __PDF_CONVERTER__
#define __PDF_CONVERTER__
#include <TH1D.h>

class BinnedPdf;
class IntegrablePdf;
class AxisCollection;

class PdfConverter{
 public:
    PdfConverter();
    ~PdfConverter();
    
    static BinnedPdf ToBinnedPdf(const IntegrablePdf&, const AxisCollection& axes_);
    static TH1D      ToTH1D(const BinnedPdf&);
};
#endif
