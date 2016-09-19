#include <JumpPDF.h>
#include <PDF.h>
#include <Exceptions.h>
#include <algorithm>
#include <functional>

//////////////////////////////
// CONSTRUCTORS/DESTRUCTORS //
//////////////////////////////

JumpPDF::JumpPDF(PDF* f_){
  if(f_)
    fPDF = static_cast<PDF*>(f_->Clone());
  
  else
    fPDF = NULL;  
}

JumpPDF::~JumpPDF(){
  delete fPDF;
}

JumpPDF::JumpPDF(const JumpPDF& other_){
  if(other_.fPDF)
    fPDF = static_cast<PDF*>(other_.fPDF->Clone());
  else
    fPDF = NULL;
}

JumpPDF
JumpPDF::operator=(const JumpPDF& other_){
  if(other_.fPDF)
    fPDF = static_cast<PDF*>(other_.fPDF->Clone());
  else
    fPDF = NULL;
  return *this;
}

std::vector<double>
JumpPDF::Diff(const std::vector<double>& x_, 
                                const std::vector<double>& x2_) const{
  std::vector<double> diff = x_;
  std::transform(diff.begin(), diff.end(), x2_.begin(), 
                 diff.begin(), std::minus<double>());
  return diff;
}

std::vector<double>
JumpPDF::Sum(const std::vector<double>& x_, 
                               const std::vector<double>& x2_) const{
  std::vector<double> sum = x_;
  std::transform(sum.begin(), sum.end(), x2_.begin(), 
                 sum.begin(), std::plus<double>());
  return sum;
}

ConditionalPDF*
JumpPDF::Clone() const{
  return static_cast<ConditionalPDF*>(new JumpPDF(*this));
}

////////////////////////////////////////
// CONDITIONAL DISTRIBUTION INTERFACE //
////////////////////////////////////////

double 
JumpPDF::ConditionalProbability(const std::vector<double>& x_,
                                 const std::vector<double>& x2_){
  if(!fPDF)
    throw NULLPointerAccessError("JumpPDF::Probability",
                                 "Have you set the function?");
     
  return fPDF->operator()(Diff(x_, x2_));
}

std::vector<double> 
JumpPDF::Sample(const std::vector<double>& x2_) const{
  if(!fPDF)
    throw NULLPointerAccessError("JumpPDF::Integral",
                                 "Have you set the function?");
  std::vector<double> samp = fPDF->Sample();
  return Sum(samp, x2_);
}
double
JumpPDF::Integral(const std::vector<double>& mins_,
                                    const std::vector<double>& maxs_,
                                    const std::vector<double>& x2_) const{
  if(!fPDF)
    throw NULLPointerAccessError("JumpPDF::Integral",
                                 "Have you set the function?");
  
  return fPDF->Integral(Diff(maxs_, x2_), Diff(mins_, x2_));
}
                                      

/////////////////////////////
// FIT COMPONENT INTERFACE //
/////////////////////////////

void
JumpPDF::MakeFittable(){
  if(!fPDF)
    throw NULLPointerAccessError("JumpPDF::MakeFittable",
                                   "Have you set the function?");
    fPDF->MakeFittable();
}

std::vector<std::string>
JumpPDF::GetParameterNames() const{
  if(!fPDF)
    throw NULLPointerAccessError("JumpPDF::GetParameterNames",
                                   "Have you set the function?");
  return fPDF->GetParameterNames();
}


std::vector<double>
JumpPDF::GetParameters() const{
  if(!fPDF)
    throw NULLPointerAccessError("JumpPDF::GetParameters",
                                   "Have you set the function?");
  return fPDF->GetParameters();
}

size_t
JumpPDF::GetParameterCount() const{
  if(!fPDF)
    throw NULLPointerAccessError("JumpPDF::GetParameterCount",
                                 "Have you set the function?");
  return fPDF->GetParameterCount();
}


void
JumpPDF::SetParameters(const std::vector<double>& params_){
  if(!fPDF)
    throw NULLPointerAccessError("JumpPDF::SetParameters",
                                 "Have you set the function?");
  fPDF->SetParameters(params_);
}
