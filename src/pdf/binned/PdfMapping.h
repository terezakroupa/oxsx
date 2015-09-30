/*********************************************************************************************/
/* A square response Matix for the experiment. Takes a binned pdf and applies the detector   */
/* to produce a new BinnedPdf. Inside is a vector of vectors, component fResponse[i][j] =    */
/* R_i_j = fraction of contents in bin j of original pdf -> bin i in the output pdf          */
/* the output bin contents are then x'_j = sum(R_i_j * x_j)                                  */
/* The systematic object is responsible for pdf renormalisation - not here                   */
/*********************************************************************************************/

#ifndef __PDF_MAPPING__
#define __PDF_MAPPING__
#include <AxisCollection.h>
#include <armadillo>
class BinnedPdf;

class PdfMapping{
 public:
    PdfMapping() :fNBins(0), fNDims(0) {}
    PdfMapping operator = (const PdfMapping& other_);
    ~PdfMapping() {}

    BinnedPdf operator() (const BinnedPdf& pdf_) const;

    void SetResponse(const arma::mat& response_);
    void SetColumn(size_t index, const std::vector<double>& column_);
    void SetRow(size_t index, const std::vector<double>& row_);
    void SetComponent(size_t column_, size_t row_, double val_);
    double GetComponent(size_t column_, size_t row_) const;

    const AxisCollection& GetAxes() const;
    void SetAxes(const AxisCollection& axes_);
    size_t GetNBins() const {return fNBins;}
    
 private:
    AxisCollection fAxes;
    arma::mat fResponse;
    unsigned fNBins;
    unsigned fNDims;

};
#endif
