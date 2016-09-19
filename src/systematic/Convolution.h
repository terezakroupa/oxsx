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

class ConditionalPDF;
class PDF;
class Convolution : public Systematic{
 public:
    Convolution(): fDist(NULL), fCachedCompatibleBins(false) {}
    ~Convolution();
    void SetFunction(PDF* function_);
    void SetConditionalPDF(ConditionalPDF* function_);
    void Construct();    

    // Make this fittable, by delegating to the underlying function
    void MakeFittable();
    std::vector<std::string> GetParameterNames() const;
    std::vector<double>      GetParameters() const;
    size_t                   GetParameterCount() const;
    void                     SetParameters(const std::vector<double>&);

 private:
    void                     Reset();
    ConditionalPDF*          fDist;
    bool                     fCachedCompatibleBins;

    AxisCollection     fSubMapAxes;
    void  CacheCompatibleBins();
    std::vector<std::vector<size_t> > fCompatibleBins;
    // the systematic subMap bin for each global bin of pdf
    std::vector<size_t> fSysBins; 
    
};
#endif
