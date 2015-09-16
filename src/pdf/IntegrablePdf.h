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

    void SetParams(const std::vector<double>& params_) {fParams = params_;}
    void SetParam(size_t index_, double val) {fParams[index_] = val;}

    std::vector<double> GetParams()  const {return fParams;}
    double GetParam(size_t index_)   const {return fParams.at(index_);}
    
 private:
    std::vector<double> fParams;
};
#endif
