/*****************************************************************************************************/
/* A gaussian pdf, gives the probability of a given observation vector.                              */
/* Parameters are contained in fParams in the IntegralPdf object, ordered (mean_0, sigma_0,          */
/*  mean_1, sigma_1.....)                                                                            */
/* These can be set using SetMean etc, or using the generic SetParameter interface from IntegrablePdf*/
/* The latter is required  to use this pdf as a convolution systematic that can be adjusted in a fit */
/* Currently assumes variables are independent. Include covariance matrix to upgrade                 */
/* params are stored like mean1, sigma1, mean2, sigma2 etc..                                         */
/*****************************************************************************************************/

#ifndef __GAUSSIAN__
#define __GAUSSIAN__
#include <IntegrablePdf.h>

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
    
    double GetMean(size_t dimension_) const;
    double GetStDev(size_t dimension_) const;
    
    virtual void Normalise() {};
    virtual double Integral() const {return 1;}
    double Integral(const std::vector<double>& mins_, const std::vector<double>& maxs_) const;
    double Integral(double mins_, double max_) const;
    virtual Pdf* Clone() const; // required for composition of pdfs
};
#endif
