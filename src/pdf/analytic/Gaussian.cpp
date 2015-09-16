#include <Gaussian.h>
#include <math.h>

Gaussian::Gaussian(size_t nDims_){
    fNDims = nDims_;
}

Gaussian::Gaussian(double mean_, double stdDev_){
    if(stdDev_ <= 0)
        throw 0; // should throw something better
    fNDims = 1;
    std::vector<double> params;
    params.push_back(mean_);
    params.push_back(stdDev_);
    SetParams(params);
}

Gaussian::Gaussian(const std::vector<double>& means_, const std::vector<double>& stdDevs_){
    if(means_.size() != stdDevs_.size())
        throw 0;
    fNDims = means_.size();
    std::vector<double> params(fNDims * 2, 0);
    for(size_t i = 0; i < means_.size(); i++){
        params.push_back(means_.at(i));
        params.push_back(stdDevs_.at(i));
    }
    SetParams(params);
}

Gaussian::Gaussian(const Gaussian& other_) : IntegrablePdf(other_){
    fNDims = other_.fNDims;
    SetParams(other_.GetParams());
}

double 
Gaussian::operator() (const std::vector<double>& vals_) const{
    if (vals_.size() != fNDims)
        throw 0; // should throw dimension error

    double exponent = 0;
    for(size_t i = 0; i < fNDims; i++){
        double mean  = GetMean(i);
        double stDev = GetStDev(i);

        double nDevs = (vals_[i] - mean)/stDev;
        exponent += nDevs * nDevs;
    }
    double norm = sqrt(2*M_PI);
    for(size_t i = 0; i < fNDims; i++)
        norm *= GetStDev(i);
    return exp(- 0.5 * exponent) / norm; 
}

double 
Gaussian::Integral(const std::vector<double>& mins_, const std::vector<double>& maxs_) const{
    if(mins_.size() != fNDims || maxs_.size() != fNDims)
        throw 0; // should throw dimension error

    double integral = 1;
    for(size_t i = 0; i < mins_.size(); i++)
        integral *= ( Cdf(i, maxs_[i]) - Cdf(i, mins_[i]));
    return integral;  
}

double 
Gaussian::Integral(double min_, double max_) const{
    return Integral(std::vector<double>(1, min_), std::vector<double>(1,max_) );
}

Pdf* 
Gaussian::Clone() const{
    return static_cast<Pdf*> (new Gaussian(*this));
}

double 
Gaussian::Cdf(size_t dim_, double val_) const{
    return 0.5 * ( 1 + erf( (val_ - GetMean(dim_)  / (sqrt(2) * GetStDev(dim_)) ) ));
}

double 
Gaussian::GetMean(size_t dimension_) const{
    return GetParam(dimension_ * 2);
}

double 
Gaussian::GetStDev(size_t dimension_) const{
    return GetParam(dimension_ * 2 -1);
}
