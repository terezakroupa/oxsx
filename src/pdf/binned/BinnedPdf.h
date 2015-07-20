#ifndef __BINNED_PDF__
#define __BINNED_PDF__
#include "AxisCollection.h"
#include "../Pdf.h"
#include <vector>

class BinnedPdf : public Pdf{
 public:
    BinnedPdf(const AxisCollection& axes_);
    BinnedPdf(const BinnedPdf& other_);
    
    virtual double operator() (const std::vector<double>& vals_) const;
    virtual double Integral()  const;
    virtual void   Normalise();
    virtual  Pdf*  Clone() const;
    
    void   Fill(const std::vector<double>& vals_);
    size_t FindBin(const std::vector<double>& vals_) const;

 private:
    AxisCollection fAxes;
    std::vector<double> fBinContents;
    size_t fNDims;
    size_t fNBins;
};

#endif
