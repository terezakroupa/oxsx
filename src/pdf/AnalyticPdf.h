#ifndef __OXSX_ANALYTIC_PDF__
#define __OXSX_ANALYTIC_PDF__
#include <Pdf.h>
#include <FitComponent.h>

class IntegrableFunction;
class AnalyticPdf : public Pdf, public FitComponent{
 public:
    AnalyticPdf(IntegrableFunction*); // make a copy
    AnalyticPdf(const AnalyticPdf& other_); // deep copy
    ~AnalyticPdf();         // frees fFunction
    Pdf* Clone() const;
    
    double operator()(const std::vector<double>& vals_) const;
    double Integral() const;
    void   Normalise();
    
    // Delegate to function
    void MakeFittable();

 private:
    IntegrableFunction* fFunction;
    double              fNorm;
};
#endif
