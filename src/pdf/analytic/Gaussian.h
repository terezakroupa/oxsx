#ifndef __GAUSSIAN__
#define __GAUSSIAN__
#include "../Pdf.h"

class Gaussian : public Pdf{
 public:
    Gaussian(size_t nDims_);
    Gaussian(double mean_, double stdDev_);
    Gaussian(const Gaussian& other_);

    virtual double operator()(const std::vector<double>& vals_) const;

    void SetMeans(const std::vector<double>& means_);
    void SetStdDevs(const std::vector<double>& stdDevs_);
    
    virtual void Normalise() {};
    virtual double Integral() const {return 1;}
    virtual Pdf* Clone() const;

 private:
    std::vector<double> fMeans;
    std::vector<double> fStdDevs;
    size_t fNDims;
};
#endif
