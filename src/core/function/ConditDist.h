#ifndef __OXSX_CONDITDIST__
#define __OXSX_CONDITDIST__
#include <FitComponent.h>
#include <vector>

class ConditDist : public FitComponent{
 public:
  virtual ~ConditDist() {};
  virtual ConditDist* Clone() const = 0;
  virtual double ConditionalProbability(const std::vector<double>& x_, 
										const std::vector<double>& x2_) = 0;
  
  virtual double Integral(const std::vector<double>& mins_,
						  const std::vector<double>& maxs_,
						  const std::vector<double>& x2_) const = 0;

  virtual double Integral(double x2_) const = 0;

  virtual std::vector<double> Sample(const std::vector<double>& x2_) const = 0;
};
#endif
