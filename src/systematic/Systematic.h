/***************************************************************************************************/
/* A systematic object is responsible for manipulating the indicies of a pdf to match those of     */
/* its underlying detector response matrix so the response can be applied. And modifying the       */
/* response matrix according to some set of parameters.                                            */
/* The class knows the data representation of the indicies it affects, as well as the rep of       */
   /*    the pdfs it acts on, this is nessecary to properly calulate its affect                    */
/* The construct() method is called in fit routines to recalculate the matrix after pdf adjustment */
/* Classes derived from this construct the response matrix according to some physical process.     */
/***************************************************************************************************/

#ifndef __OXSX_SYSTEMATIC__
#define __OXSX_SYSTEMATIC__
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

    void SetPdfDataRep(const DataRepresentation&);
    DataRepresentation GetPdfDataRep() const;

    virtual void   SetParameters(const std::vector<double>&);
    virtual std::vector<double> GetParameters() const;

    virtual void   SetParameter(size_t index_, double val_);
    virtual double GetParameter(size_t index_) const;
    
     size_t GetParamCount() const;

     virtual void Construct() {}

 protected:
    PdfMapping fPdfMapping;
    std::vector<double> fParams;
    DataRepresentation fDataRep;     // the data indicies that this systematic acts on
    DataRepresentation fPdfDataRep;  
    // the data indices  of the pdfs it will act on, needs to be at least the lenth of the 
    // systematics representation
    
    // methods below used for index manipilation between pdf and response
    bool BinsCompatible(size_t bin1 , size_t bin2) const;
    bool VectorContains(const std::vector<size_t>&, size_t) const;
};
#endif
