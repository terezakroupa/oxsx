/***********************************************************************************/
/* Responsible for generating a new pdf given a detector response and an input pdf */
/***********************************************************************************/

#ifndef __PDF_MAPPING__
#define __PDF_MAPPING__
#include <AxisCollection.h>
class BinnedPdf;

class PdfMapping{
 public:
    PdfMapping()  {}
    PdfMapping operator = (const PdfMapping& other_);
    ~PdfMapping() {}

    BinnedPdf operator() (const BinnedPdf& pdf_, const std::vector<size_t>& indicies_) const;

    void SetResponse(const std::vector<std::vector<double> >& response_);
    void SetColumn(size_t index, const std::vector<double>& column_);
    void SetRow(size_t index, const std::vector<double>& row_);
    void SetComponent(size_t column_, size_t row_, double val_);

    const AxisCollection& GetAxes() const;
    void SetAxes(const AxisCollection& axes_);
    size_t GetNBins() const {return fNBins;}
    
 private:
    AxisCollection fAxes;
    std::vector<std::vector<double> > fResponse; // inner is the row
    unsigned fNBins;
    unsigned fNDims;

};
#endif
