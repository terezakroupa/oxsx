/******************************************************************/
/* Convolve a binned pdf with an integrable pdf to give a new pdf */
/******************************************************************/

#ifndef __CONVOLUTION__
#define __CONVOLUTION__
#include <Systematic.h>

class IntegrablePdf;
class Convolution : public Systematic{
 public:
    Convolution():fPdf(NULL) {}
    ~Convolution();
    void SetPdf(IntegrablePdf* pdf_);
    void SetAxes(const AxisCollection& axes_);
    void Construct();    

    void SetParameters(const std::vector<double>& params_);
    std::vector<double> GetParameters() const;

    double GetParameter(size_t index_) const;
    void   SetParameter(size_t index_, double val);

 private:
    void   Reset();
    IntegrablePdf* fPdf;
    
};
#endif

