#ifndef __OXSX_GAUSSIAN__
#define __OXSX_GAUSSIAN__
#include <Function.h>
#include <gsl/gsl_cdf.h>

class Gaussian2 : public Function{
 public:
    // Constructory things
    Gaussian2(size_t nDims_);
    Gaussian2(double mean_, double stdDev_);
    Gaussian2(const std::vector<double>& mean_, 
             const std::vector<double>& stdDev_);
    virtual Function* Clone() const;


    virtual double operator()(const std::vector<double>& vals_) const;
    double  Cdf(size_t dim_, double val_) const;


    // Getters/Setter
    void SetMeans(const std::vector<double>& means_);
    void SetStdDevs(const std::vector<double>& stdDevs_);
    
    double GetMean(size_t dimension_) const;
    double GetStDev(size_t dimension_) const;
    
    double Integral(const std::vector<double>& mins_, 
                    const std::vector<double>& maxs_) const;

    double Integral(double mins_, double max_) const;

    double GetCdfCutOff() const;
    void   SetCdfCutOff(double);

 private:
    double fCdfCutOff; // number of stDevs away from the mean 
                       // assumed to be zero or 1 for speed integration
};
#endif
