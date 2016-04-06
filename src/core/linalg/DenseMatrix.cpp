#include <DenseMatrix.h>
#include <PdfExceptions.h>
#include <Vector.h>

DenseMatrix::DenseMatrix(int nRows_, int nCols_){
    fArmaMat = arma::mat(nRows_, nCols_);
}

DenseMatrix::DenseMatrix(const arma::mat& mat_){
    fArmaMat = mat_;
}

double&
DenseMatrix::operator()(int row_, int col_){
    try{
        return fArmaMat(row_, col_);
    }
    catch (const std::logic_error&){
        throw OutOfBoundsError("Attempted out of bounds access on matrix!");
    }
}

int 
DenseMatrix::GetNRows() const{
    return fArmaMat.n_rows;
}

int 
DenseMatrix::GetNCols() const{
    return fArmaMat.n_cols;
}
void 
DenseMatrix::SetZeros(){
    fArmaMat.zeros();
}

Vector
DenseMatrix::Inner(const Vector& vec_) const{
    try{
        return Vector(fArmaMat * vec_.fArmaVec);
    }
    catch(const std::logic_error& e){
        throw OutOfBoundsError("Attempted matrix-vector inner product, but indices don't match!!");
    }
}

DenseMatrix
DenseMatrix::Inner(const DenseMatrix& other_) const{
    try{
        return DenseMatrix(fArmaMat * other_.fArmaMat);
    }
    catch(const std::logic_error& e){
        throw OutOfBoundsError("Attempted matrix-matrix inner product, but dimensions don't match!!");
    }
}

double
DenseMatrix::Det() const{
    try{
        return arma::det(fArmaMat);
    }
    catch(const std::logic_error& e){
        throw DimensionError("Can't calculate the determinant of non-square matrix!");
    }
}

DenseMatrix
DenseMatrix::Inverse() const{
    try{
        return DenseMatrix(arma::inv(fArmaMat));
    }
    catch(const std::logic_error& e){
        throw DimensionError("Can't calculate the inverse of non-square matrix!");
    }
    catch(const std::runtime_error& e){
        throw std::runtime_error("Can't calculate the inverse of singular matrix!");
    }
}

void
DenseMatrix::Identity(){
    fArmaMat.eye();
}

void
DenseMatrix::Identity(int n_){
    fArmaMat = arma::mat(n_, n_, arma::fill::eye);
}
