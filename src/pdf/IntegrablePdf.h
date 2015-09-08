#ifndef __INTEGRABLE_PDF__
#define __INTEGRABLE_PDF__
#include <vector>
#include <pdf.h>

class IntegrablePdf : public Pdf{
 public:
    IntegrablePdf() {}
    virtual ~IntegrablePdf() {}
    
    virtual double Integral(const std::vector<double>& mins_, 
                            const std::vector<double>& maxs_) const = 0;
};
#endif
