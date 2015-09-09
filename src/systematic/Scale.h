/*********************************************/
/* An overall scaling uncertainty on the pdf */
/*********************************************/

#ifndef __SCALE__
#include <Systematic.h>
#include <BinnedPdf.h>

class Scale : public Systematic{
 public:
    Scale(double scaleFactor_) : fScaleFactor(scaleFactor_) {}
    virtual BinnedPdf
        operator()(const BinnedPdf& pdf_, const std::vector<size_t>& indicies_) const;

 private:
    double fScaleFactor;
    
};
#endif
