/*********************************************************************************************/
/* A square response Matix for the experiment. Takes a binned pdf and applies the detector   */
/* to produce a new BinnedPhysDist. Inside is a vector of vectors, component fResponse[i][j] =    */
/* R_i_j = fraction of contents in bin j of original pdf -> bin i in the output pdf          */
/* the output bin contents are then x'_j = sum(R_i_j * x_j)                                  */
/* The systematic object is responsible for pdf renormalisation - not here                   */
/*********************************************************************************************/

#ifndef __OXSX_DENSE_MATRIX__
#define __OXSX_DENSE_MATRIX__
#include <AxisCollection.h>
#define ARMA_DONT_USE_CXX11
#include <armadillo>
class BinnedPhysDist;

class DenseMatrix{
 public:
    DenseMatrix() :fNBins(0), fNDims(0) {}
    ~DenseMatrix() {}

    std::vector<double> operator() (const std::vector<double>& input_) const;

    void   SetComponent(size_t column_, size_t row_, double val_);
    double GetComponent(size_t column_, size_t row_) const;
    
    DenseMatrix operator*=(const DenseMatrix& other_);

    const AxisCollection& GetAxes() const;
    void   SetAxes(const AxisCollection& axes_);
    size_t GetNBins() const {return fNBins;}
    size_t GetNDims() const {return fNDims;}
    void   SetZeros();
    void   SetToIdentity();
 private:
    AxisCollection fAxes;
    arma::mat fArmaMat;
    unsigned fNBins;
    unsigned fNDims;
};
#endif
