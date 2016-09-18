#ifndef __OXSX_JUMP_DISTRIBUTION__
#define __OXSX_JUMP_DISTRIBUTION__
#include <ConditDist.h>
#include <vector>
#include <string>

class PDF;
class JumpDist : public ConditDist{
 public:  
  // Constructors/Destructor
  JumpDist(): fPDF(NULL) {}
  JumpDist(PDF*);
  ~JumpDist();
  JumpDist(const JumpDist&);
  JumpDist operator=(const JumpDist&);
  ConditDist* Clone() const;

  // ConditDist Interface, just execute the function on x - x2
  virtual double ConditionalProbability(const std::vector<double>& x_,
										const std::vector<double>& x2_);
  
  virtual double Integral(const std::vector<double>& mins_,
                          const std::vector<double>& maxs_,
						  const std::vector<double>& x2_) const;
  
  virtual double Integral(double x2_) const;
  std::vector<double> Sample(const std::vector<double>& x2_) const;

  // Elementwise difference/sum between x and x2
  std::vector<double> Diff(const std::vector<double>& x_, 
						   const std::vector<double>& x2_) const;

  std::vector<double> Sum(const std::vector<double>& x_, 
                          const std::vector<double>& x2_) const;

  // Fit Component Interface - defer to the underlying function
  void MakeFittable();
  std::vector<std::string> GetParameterNames() const;
  std::vector<double> GetParameters() const;
  size_t GetParameterCount() const; 
  void SetParameters(const std::vector<double>& params_);

 private:
  PDF* fPDF;
};
#endif
