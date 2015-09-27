/*****************************************************************************************************/
/* Convolution of the pdf with another compatible pdf. The pdf must have dimensionality smaller than */
/* the pdfs it will act on, and must implement IntegrablePdf method Integrate() to allow the         */
/* convolution to integrate it over bin boundaries.                                                  */
/* The parameters set in this systematic are forwarded on to the internal pdf, you then need to call */
/* Construct() to update the response matrix                                                         */
/*****************************************************************************************************/

#ifndef __OXSX_CONVOLUTION__
#define __OXSX_CONVOLUTION__
#include <Systematic.h>

class IntegrablePdf;
class Convolution : public Systematic{
 public:
    Convolution():fPdf(NULL), fHasAxes(false), fCachedCompatibleBins(false) {}
    ~Convolution();
    void SetPdf(IntegrablePdf* pdf_);
    void SetAxes(const AxisCollection& axes_);
    void Construct();    

    void SetParameters(const std::vector<double>& params_);
    std::vector<double> GetParameters() const;

    double GetParameter(size_t index_) const;
    void   SetParameter(size_t index_, double val);

 private:
    void           Reset();
    IntegrablePdf* fPdf;
    size_t         fParameterCount;
    bool           fHasAxes;
    bool           fCachedCompatibleBins;

    void  CacheCompatibleBins();
    std::vector<std::vector<size_t> > fCompatibleBins;
};
#endif

