/***************************************************************************************************/
/* A pdf that can be integrated over any range of its domain, and can be parameterised by a set of */
/* numbers.                                                                                        */
/* This base class is blind to the significance of the parameters but the generic interface allows */
/* them to be adjusted in a fit                                                                    */
/***************************************************************************************************/

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

    void SetParameters(const std::vector<double>& params_); 
    void SetParameter(size_t index_, double val_); 

    std::vector<double> GetParameters()  const; 
    double GetParameter(size_t index_)   const; 
    
 private:
    std::vector<double> fParams;
};
#endif
