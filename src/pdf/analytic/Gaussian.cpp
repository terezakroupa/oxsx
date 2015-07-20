#include "Gaussian.h"
#include <math.h>
static const double pi = 3.14159; //replace this

Gaussian::Gaussian(size_t nDims_){
    fNDims = nDims_;
}

Gaussian::Gaussian(double mean_, double stdDev_){
    if(stdDev_ <= 0)
        throw 0; // should throw something better
    fNDims = 1;
    fMeans   = std::vector<double>(1,mean_);
    fStdDevs = std::vector<double>(1,stdDev_);
}

Gaussian::Gaussian(const Gaussian& other_){
    fNDims = other_.fNDims;
    fMeans = other_.fMeans;
    fStdDevs = other_.fStdDevs;
}

double Gaussian::operator() (const std::vector<double>& vals_) const{
    if (vals_.size() != fNDims)
        throw 0; // should throw dimension error

    double exponent = 0;
    for(size_t i = 0; i < fNDims; i++){
        double nDevs = (vals_[i] - fMeans[i])/fStdDevs[i];
        exponent += nDevs * nDevs;
    }
    double norm = sqrt(2*pi);
    for(size_t i = 0; i < fNDims; i++)
        norm *= fStdDevs[i];
    return exp(- 0.5 * exponent) / norm; 
}


void Gaussian::SetMeans(const std::vector<double>& means_){
    if (means_.size() != fNDims)
        throw 0; // should throw dimension error
    fMeans = means_;
}

void Gaussian::SetStdDevs(const std::vector<double>& stdDevs_){
    if (stdDevs_.size() != fNDims)
        throw 0; // should throw dimension error
    fStdDevs = stdDevs_;
}

Pdf* Gaussian::Clone() const{
    return static_cast<Pdf*> (new Gaussian(*this));
}
