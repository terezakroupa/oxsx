/**************************************************************************/
/* Responsible for constructing a response matrix and forwarding the call */
/**************************************************************************/

#ifndef __SYSTEMATIC__
#define __SYSTEMATIC__
#include <PdfMapping.h>
#include <BinnedPdf.h>
#include <DataRepresentation.h>
#include <vector>

class Systematic{
 public:
    Systematic()   {}
    virtual ~Systematic()  {}

    BinnedPdf 
    operator()(const BinnedPdf& pdf_) const;
        
    void 
    SetResponse(const std::vector<std::vector<double> >& responseMatrix_);
    const PdfMapping& GetResponse() const;
        
    void SetDataRep(const DataRepresentation&);
    DataRepresentation GetDataRep() const;

    void SetParameters(const std::vector<double>&);
    const std::vector<double>& GetParameters() const;
    size_t GetParamCount() const;

 protected:
    PdfMapping fPdfMapping;
    std::vector<double> fParams;
    DataRepresentation fDataRep;
};
#endif
