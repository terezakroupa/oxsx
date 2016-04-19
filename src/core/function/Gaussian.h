#ifndef __OXSX_GAUSSIAN__
#define __OXSX_GAUSSIAN__
#include <IntegrableFunction.h>
#include <ParameterManager.h>

class Gaussian : public IntegrableFunction{
 public:
    // Constructory things
    Gaussian(size_t nDims_); // means = 0, stdDevs = 1
    Gaussian(double mean_, double stdDev_);
    Gaussian(const std::vector<double>& mean_, 
             const std::vector<double>& stdDev_);
    virtual   Function* Clone() const;

    // Probability
    virtual double operator()(const std::vector<double>& vals_) const;
    double  Cdf(size_t dim_, double val_) const;
    double Integral(const std::vector<double>& mins_, 
                    const std::vector<double>& maxs_) const;
    double Integral() const {return 1;} // normalised by definition

    // Getters/Setters
    void SetMeansStdDevs(const std::vector<double>& means_, 
                         const std::vector<double>& stdDevs_);
    double GetMean(size_t dimension_) const;
    double GetStDev(size_t dimension_) const;    
    std::vector<double> GetMeans() const;
    std::vector<double> GetStdDevs() const;
    double GetCdfCutOff() const;
    void   SetCdfCutOff(double);
    int    GetNDims() const;

    // Make this object fittable    
    void MakeFittable();
    std::vector<double> GetParameters() const;
    std::vector<std::string> GetParameterNames() const;
    void   SetParameters(const std::vector<double>&);
    size_t GetParameterCount() const;
    

 private:
    ParameterManager fParameterManager;
    std::vector<double> fMeans;
    std::vector<double> fStdDevs;
    
    double fCdfCutOff; // number of stDevs away from the mean                                       // assumed to be zero or 1 for speed integration
    int fNDims;
    
    void   Initialise(const std::vector<double>& means_, 
                      const std::vector<double>& stdDevs_);
};
#endif
