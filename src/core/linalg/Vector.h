#ifndef __OXSX_VECTOR__
#define __OXSX_VECTOR__
#include <DenseMatrix.h>
#include <armadillo>
#include <vector>


class Vector{
 public:
    // cnstrs
    Vector() {}
    Vector(int size_); // initialised memory
    Vector(int size_, double val_);
    Vector(const arma::vec& vec_);
    Vector(const std::vector<double>& stlVec_);
    
    // conversion
    std::vector<double> AsSTL() const;

    // length
    void   Clear();
    size_t GetNDims() const;

    // element access
    double&       operator()(size_t index_);
    const double& operator()(size_t index_) const;
    
    // all values at once
    void Zeros();
    void Fill(double val_);

    double Norm() const;

    // Products
    double Inner(const Vector& other_) const;
    Vector Scalar(double) const;

    // Sums
    Vector operator- (const Vector& other_) const;
    Vector operator+ (const Vector& other_) const;

    // Matrix product implementations need the underlying vector
    friend Vector DenseMatrix::Inner(const Vector&) const;

 private:
    arma::vec fArmaVec;
};
#endif
