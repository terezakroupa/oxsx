#ifndef __OXSX_JUMP_PDF__
#define __OXSX_JUMP_PDF__
#include <ConditionalPDF.h>
#include <vector>
#include <string>

class PDF;
class JumpPDF : public ConditionalPDF{
 public:  
  // Constructors/Destructor
  JumpPDF(): fPDF(NULL) {}
  JumpPDF(PDF*);
  ~JumpPDF();
  JumpPDF(const JumpPDF&);
  JumpPDF operator=(const JumpPDF&);
  ConditionalPDF* Clone() const;

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
