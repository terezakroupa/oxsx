#ifndef __OXSX_DENSE_MATRIX__
#define __OXSX_DENSE_MATRIX__
#include <armadillo>
class Vector;

class DenseMatrix{
 public:
    // Cnstrs
    DenseMatrix(){}
    DenseMatrix(int nRows_, int nCols_); // memory uninitialised
    DenseMatrix(const arma::mat&);

    // Access
    double& operator()(int row_, int col_);
    int GetNRows() const;
    int GetNCols() const;
    
    void SetZeros();    
    void Identity();
    void Identity(int n_);

    // Linalg
    Vector      Inner(const Vector&) const; // friend function of Vector
    DenseMatrix Inner(const DenseMatrix&) const;

    DenseMatrix Inverse() const;
    double Det() const;



 private:
    arma::mat fArmaMat;
};
#endif
