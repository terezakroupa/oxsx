#ifndef __OXSX_ANALYTIC_PDF__
#define __OXSX_ANALYTIC_PDF__
#include <Pdf.h>
#include <FitComponent.h>
#include <DataRepresentation.h>

class IntegrableFunction;
class AnalyticPdf : public Pdf, public FitComponent{
 public:
    AnalyticPdf(IntegrableFunction*); // make a copy
    AnalyticPdf(const AnalyticPdf& other_); // deep copy
    ~AnalyticPdf();         // frees fFunction
    Pdf* Clone() const;
    
    double operator()(const std::vector<double>& vals_) const;
    double Probability(const EventData&) const;
    double Integral() const;
    void   Normalise();

    void SetDataRep(const DataRepresentation&);
    DataRepresentation GetDataRep() const;
    
    unsigned GetNDims() const;

    // Delegate to function
    void MakeFittable();

 private:
    DataRepresentation  fDataRep;
    IntegrableFunction* fFunction;
    double              fNorm;
};
#endif
