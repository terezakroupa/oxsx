#ifndef __COMPOSITE_PDF__
#define __COMPOSITE_PDF__
#include <Pdf.h>
#include <vector>
class EventData;

class CompositePdf : public Pdf{
 public:
    CompositePdf(const Pdf* p1_, const Pdf* p2_);
    CompositePdf(const std::vector<Pdf*>& pdfs_); 
    virtual ~CompositePdf();

    virtual double operator() (const std::vector<double>& vals_) const;
    virtual double Probability(const EventData&) const;
    virtual Pdf* Clone() const;

    virtual double Integral()  const;
    virtual void   Normalise();
    
 private:
    std::vector<Pdf*> fPdfPtrs;
};
#endif
