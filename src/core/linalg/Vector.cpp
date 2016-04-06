#include <Vector.h>
#include <PdfExceptions.h>

Vector::Vector(const arma::vec& vec_){
    fArmaVec = vec_;
}

Vector::Vector(const std::vector<double>& stlVec_){
    fArmaVec = arma::vec(stlVec_);
}

Vector::Vector(int size_){
    fArmaVec = arma::vec(size_);
}

Vector::Vector(int size_, double val_){
    fArmaVec = arma::vec(size_);
    fArmaVec.fill(val_);
}

std::vector<double> 
Vector::AsSTL() const{
    return arma::conv_to<std::vector<double> >::from(fArmaVec);
}

void
Vector::Clear(){
    fArmaVec.reset();
}

size_t
Vector::GetNDims() const{
    return fArmaVec.size();
}

void
Vector::Zeros(){
    fArmaVec.zeros();
}

void
Vector::Fill(double val_){
    fArmaVec.fill(val_);
}

double&
Vector::operator()(size_t index_){
    try{
        return fArmaVec(index_);
    }
    catch(const std::logic_error& e){
        throw OutOfBoundsError("Attempted out of bounds access on vector!");
    }
}

const double&
Vector::operator()(size_t index_) const{
    try{
        return fArmaVec(index_);
    }
    catch(const std::logic_error& e){
        throw OutOfBoundsError("Attempted out of bounds access on vector!");
    }
}

double
Vector::Norm() const{
    return arma::norm(fArmaVec);
}

double
Vector::Inner(const Vector& other_) const{
    try{
        return arma::dot(fArmaVec, other_.fArmaVec);
    }
    catch (const std::logic_error& e){
        throw OutOfBoundsError("Attempted inner product on different dimensionality vectors!");
    }
}

Vector
Vector::Scalar(double s) const{
    return Vector(fArmaVec * s);
}

Vector
Vector::operator-(const Vector& other_) const{
    return Vector(fArmaVec - other_.fArmaVec);
}

Vector
Vector::operator+(const Vector& other_) const{
    return Vector(fArmaVec + other_.fArmaVec);
}
