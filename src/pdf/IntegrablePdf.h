#ifndef __INTEGRABLE_PDF__
#define __INTEGRABLE_PDF__
#include <vector>
#include <pdf.h>

class IntegrablePdf : public Pdf{
 public:
    IntegrablePdf() {}
    IntegrablePdf(const IntegrablePdf& other_) : Pdf(other_) {}
    virtual ~IntegrablePdf() {}
    
    virtual double Integral(const std::vector<double>& mins_, 
                            const std::vector<double>& maxs_) const = 0;

    void SetParameters(const std::vector<double>& params_) {fParams = params_;}
    void SetParameter(size_t index_, double val_) { fParams[index_] = val_;}

    std::vector<double> GetParameters()  const {return fParams;}
    double GetParameter(size_t index_)   const {return fParams.at(index_);}
    
 private:
    std::vector<double> fParams;
};
#endif
