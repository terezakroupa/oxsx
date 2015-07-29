#ifndef __GAUSSIAN__
#define __GAUSSIAN__
#include "../IntegrablePdf.h"

// Currently assumes variables are independent. Include covariance matrix to upgrade
class Gaussian : public IntegrablePdf{
 public:
    Gaussian(size_t nDims_);
    Gaussian(double mean_, double stdDev_);
    Gaussian(const std::vector<double>& mean_, const std::vector<double>& stdDev_);
    Gaussian(const Gaussian& other_);

    virtual double operator()(const std::vector<double>& vals_) const;
    double  Cdf(size_t dim_, double val_) const;

    void SetMeans(const std::vector<double>& means_);
    void SetStdDevs(const std::vector<double>& stdDevs_);
    
    virtual void Normalise() {};
    virtual double Integral() const {return 1;}
    double Integral(const std::vector<double>& mins_, const std::vector<double>& maxs_) const;
    double Integral(double mins_, double max_) const;
    virtual Pdf* Clone() const;

    
 private:
    std::vector<double> fMeans;
    std::vector<double> fStdDevs;
};
#endif
