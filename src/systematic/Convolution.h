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

class ConditionalDistribution;
class IntegrableFunction;
class Convolution : public Systematic{
 public:
    Convolution(): fDist(NULL), fHasAxes(false), fCachedCompatibleBins(false) {}
    ~Convolution();
    void SetFunction(IntegrableFunction* function_);
    void SetConditionalDistribution(ConditionalDistribution* function_);
    void SetAxes(const AxisCollection& axes_);
    void Construct();    

    // Make this fittable, by delegating to the underlying function
    void MakeFittable();
    std::vector<std::string> GetParameterNames() const;
    std::vector<double>      GetParameters() const;
    size_t                   GetParameterCount() const;
    void                     SetParameters(const std::vector<double>&);

 private:
    void                     Reset();
    ConditionalDistribution* fDist;
    bool                     fHasAxes;
    bool                     fCachedCompatibleBins;

    AxisCollection fSysAxes;
    void  CacheCompatibleBins();
    std::vector<std::vector<size_t> > fCompatibleBins;
    // the systematic subMap bin for each global bin of pdf
    std::vector<size_t> fSysBins; 
    
};
#endif

