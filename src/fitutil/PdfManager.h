#ifndef __OXSX_PDF_MANAGER__
#define __OXSX_PDF_MANAGER__
#include <FitComponent.h>
#include <vector>

class Pdf;
class EventData;

class PdfManager : public FitComponent{
 public:
    PdfManager(): fNPdfs(0), fNDims(0) {}
    ~PdfManager(); // free pdf copies

    void  AddPdf(Pdf *); // take a copy
    void  AddPdfs(const std::vector<Pdf*>& pdfs_);

    const std::vector<double>& GetNormalisations() const;
    void  SetNormalisations(const std::vector<double>&);
    
    double Probability(const EventData&) const;
    
    size_t GetNPdfs() const;
    size_t GetNDims() const;
    
    // Make a fittable component - i.e. rescale pdfs inside to fit
    void  MakeFittable();    

 private:
    size_t fNPdfs;
    size_t fNDims;
    std::vector<Pdf*>   fPdfs;
    std::vector<double> fNormalisations;
};
#endif
