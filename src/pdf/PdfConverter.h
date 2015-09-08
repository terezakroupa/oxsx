/*****************************************************************************************************/
/* A class that converts an integrable analytic pdf for a binned one for comparison with binned pdfs */
/*****************************************************************************************************/
#ifndef __PDF_CONVERTER__
#define __PDF_CONVERTER__

class BinnedPdf;
class IntegrablePdf;
class AxisCollection;

class PdfConverter{
 public:
    PdfConverter();
    ~PdfConverter();
    
    static BinnedPdf ToBinnedPdf(const IntegrablePdf&, const AxisCollection& axes_);
};
#endif
