#include <Gaussian2.h>
#include <math.h>
#include <PdfExceptions.h>
#include <iostream>

// Set/Get Parameters are the protected interface from base class Integrable Pdf

Gaussian2::Gaussian2(size_t nDims_){
    fNDims = nDims_;
    fCdfCutOff = 6; // default val
}

Gaussian2::Gaussian2(double mean_, double stdDev_){
    if(stdDev_ <= 0)
        throw ParameterError("Gaussian2 standard deviation must be greater than 0!");
    fNDims = 1;

    std::vector<double> params;
    params.push_back(mean_);
    params.push_back(stdDev_);
    SetParameters(params);

    fCdfCutOff = 6; // default val
}

Gaussian2::Gaussian2(const std::vector<double>& means_, const std::vector<double>& stdDevs_){
    if(means_.size() != stdDevs_.size())
        throw DimensionError("Gaussian2: Unequal number of means and std devs");

    fNDims = means_.size();
    std::vector<double> params(fNDims * 2, 0);
    for(size_t i = 0; i < means_.size(); i++){
        params[2 * i] = means_.at(i);
        params[2 * i + 1] = stdDevs_.at(i);
    }
    SetParameters(params);
    fCdfCutOff = 6; // default val
}

double 
Gaussian2::operator() (const std::vector<double>& vals_) const{
    if (vals_.size() != fNDims)
        throw DimensionError("Gaussian2 dimensionality does not match the observable vector passed!");

    if(GetParameters().size() != 2 * fNDims)
        throw DimensionError("Gaussian2:  Wrong number of params to evaluate probability");

    double exponent = 0;
    for(size_t i = 0; i < fNDims; i++){
        double mean  = GetMean(i);
        double stDev = GetStDev(i);

        double nDevs = (vals_.at(i) - mean)/stDev;
        exponent += nDevs * nDevs;
    }
    double norm = 1;
    for(size_t i = 0; i < fNDims; i++)
        norm *= sqrt(2*M_PI) * GetStDev(i);
    return exp(- 0.5 * exponent) / norm; 
}

double 
Gaussian2::Integral(const std::vector<double>& mins_, const std::vector<double>& maxs_) const{
    if(mins_.size() != fNDims || maxs_.size() != fNDims)
        throw DimensionError("Gaussian2, tried to integrate over interval of wrong dimensionality");

    double integral = 1;
    for(size_t i = 0; i < mins_.size(); i++)
        integral *= ( Cdf(i, maxs_[i]) - Cdf(i, mins_[i]));
  
    return integral;  
}

double 
Gaussian2::Integral(double min_, double max_) const{
    return Integral(std::vector<double>(1, min_), std::vector<double>(1,max_) );
}

Function* 
Gaussian2::Clone() const{
    return static_cast<Function*> (new Gaussian2(*this));
}

double 
Gaussian2::Cdf(size_t dim_, double val_) const{
    double nDevs = (val_ - GetMean(dim_))/GetStDev(dim_);
    if (nDevs > fCdfCutOff)
        return 1;
    if(nDevs < -1 * fCdfCutOff)
        return 0;

    return gsl_cdf_gaussian_P(val_ - GetMean(dim_), GetStDev(dim_));
}

double 
Gaussian2::GetMean(size_t dimension_) const{
    return GetParameter(dimension_ * 2);
}

double 
Gaussian2::GetStDev(size_t dimension_) const{
    return GetParameter(dimension_ * 2 + 1);
}

double
Gaussian2::GetCdfCutOff() const{
    return fCdfCutOff;
}

void 
Gaussian2::SetCdfCutOff(double cutOff_){
    fCdfCutOff = cutOff_;
}
