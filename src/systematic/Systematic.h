/***************************************************************************************************/
/* A systematic object is responsible for manipulating the indicies of a pdf to match those of     */
/* its underlying detector response matrix so the response can be applied. And modifying the       */
/* response matrix according to some set of parameters.                                            */
/* The class knows the data representation of the indicies it affects, as well as the rep of       */
/*    the pdfs it acts on, this is nessecary to properly calulate its affect                       */
/* The construct() method is called in fit routines to recalculate the matrix after pdf adjustment */
/* Classes derived from this construct the response matrix according to some physical process.     */
/***************************************************************************************************/

#ifndef __OXSX_SYSTEMATIC__
#define __OXSX_SYSTEMATIC__
#include <Matrix.h>
#include <BinnedPhysDist.h>
#include <FitComponent.h>
#include <DataRepresentation.h>
#include <vector>

class Systematic : public FitComponent{
 public:
    virtual ~Systematic()  {}

    BinnedPhysDist 
    operator()(const BinnedPhysDist& pdf_) const;
        
    void 
    SetResponse(const Matrix& responseMatrix_);
    const Matrix& GetResponse() const;
        
    void SetDataRep(const DataRepresentation&);
    DataRepresentation GetDataRep() const;

    void SetPdfDataRep(const DataRepresentation&);
    DataRepresentation GetPdfDataRep() const;

    virtual void Construct() = 0;

 protected:
    Matrix fResponse;
    DataRepresentation fDataRep;     // the data indicies that this systematic acts on
    DataRepresentation fPdfDataRep;  
    // the data indices  of the pdfs it will act on, needs to be at least the lenth of the 
    // systematics representation
    
    // methods below used for index manipilation between pdf and response
    bool BinsCompatible(size_t bin1 , size_t bin2) const;
    bool VectorContains(const std::vector<size_t>&, size_t) const;
};
#endif
