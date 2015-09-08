#include <Gaussian.h>
#include <math.h>

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

Gaussian::Gaussian(const std::vector<double>& means_, const std::vector<double>& stdDevs_){
    if(means_.size() != stdDevs_.size())
        throw 0;
    fNDims = means_.size();
    SetMeans(means_);
    SetStdDevs(stdDevs_);
}

Gaussian::Gaussian(const Gaussian& other_) : Pdf(other_){
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
    double norm = sqrt(2*M_PI);
    for(size_t i = 0; i < fNDims; i++)
        norm *= fStdDevs[i];
    return exp(- 0.5 * exponent) / norm; 
}

double Gaussian::Integral(const std::vector<double>& mins_, const std::vector<double>& maxs_) const{
    if(mins_.size() != fNDims || maxs_.size() != fNDims)
        throw 0; // should throw dimension error

    double integral = 1;
    for(size_t i = 0; i < mins_.size(); i++)
        integral *= ( Cdf(i, maxs_[i]) - Cdf(i, mins_[i]));
    return integral;  
}

double Gaussian::Integral(double min_, double max_) const{
    return Integral(std::vector<double>(1, min_), std::vector<double>(1,max_) );
}


void Gaussian::SetMeans(const std::vector<double>& means_){
    if (means_.size() != fNDims)
        throw 0; // should throw dimension error
    fMeans = means_;
}

void Gaussian::SetStdDevs(const std::vector<double>& stdDevs_){
    if (stdDevs_.size() != fNDims)
        throw 0; // should throw dimension error
    for(size_t i = 0; i < stdDevs_.size(); i++){
        if(stdDevs_[i] < 0)
            throw 0;
    }
    fStdDevs = stdDevs_;
}

Pdf* Gaussian::Clone() const{
    return static_cast<Pdf*> (new Gaussian(*this));
}

double Gaussian::Cdf(size_t dim_, double val_) const{
    return 0.5 * ( 1 + erf( (val_ - fMeans[dim_])  / (sqrt(2) * fStdDevs[dim_]) ) );
}
