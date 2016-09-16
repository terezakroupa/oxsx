#ifndef __OXSX_UNCONDITIONAL_DISTRIBUTION__
#define __OXSX_UNCONDITIONAL_DISTRIBUTION__
#include <ConditionalDistribution.h>
#include <vector>
#include <string>

class IntegrableFunction;
class UnconditionalDistribution : public ConditionalDistribution{
 public:  
  // Constructors/Destructor
  UnconditionalDistribution(IntegrableFunction*);
  ~UnconditionalDistribution();
  UnconditionalDistribution(const UnconditionalDistribution&);
  UnconditionalDistribution operator=(const UnconditionalDistribution&);
  ConditionalDistribution* Clone() const;

  // Conditional Distribution Interface, just execute the function on x - x2
  virtual double ConditionalProbability(const std::vector<double>& x_,
										const std::vector<double>& x2_);
  
  virtual double Integral(const std::vector<double>& mins_,
                          const std::vector<double>& maxs_,
						  const std::vector<double>& x2_) const;
  
  virtual double Integral(double x2_) const;
  std::vector<double> Sample(const std::vector<double>& x2_) const;

  // Elementwise difference between x and x2
  std::vector<double> Diff(const std::vector<double>& x_, 
						   const std::vector<double>& x2_) const;

  // Fit Component Interface - defer to the underlying function
  void MakeFittable();
  std::vector<std::string> GetParameterNames() const;
  std::vector<double> GetParameters() const;
  size_t GetParameterCount() const; 
  void SetParameters(const std::vector<double>& params_);

 private:
  IntegrableFunction* fFunction;
};
#endif
