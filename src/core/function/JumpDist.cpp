#include <JumpDist.h>
#include <PDF.h>
#include <Exceptions.h>
#include <algorithm>
#include <functional>

//////////////////////////////
// CONSTRUCTORS/DESTRUCTORS //
//////////////////////////////

JumpDist::JumpDist(PDF* f_){
  if(f_)
	fPDF = static_cast<PDF*>(f_->Clone());
  
  else
	fPDF = NULL;  
}

JumpDist::~JumpDist(){
  delete fPDF;
}

JumpDist::JumpDist(const JumpDist& other_){
  if(other_.fPDF)
	fPDF = static_cast<PDF*>(other_.fPDF->Clone());
  else
	fPDF = NULL;
}

JumpDist
JumpDist::operator=(const JumpDist& other_){
  if(other_.fPDF)
	fPDF = static_cast<PDF*>(other_.fPDF->Clone());
  else
	fPDF = NULL;
  return *this;
}

std::vector<double>
JumpDist::Diff(const std::vector<double>& x_, 
								const std::vector<double>& x2_) const{
  std::vector<double> diff = x_;
  std::transform(diff.begin(), diff.end(), x2_.begin(), 
				 diff.begin(), std::minus<double>());
  return diff;
}

std::vector<double>
JumpDist::Sum(const std::vector<double>& x_, 
							   const std::vector<double>& x2_) const{
  std::vector<double> sum = x_;
  std::transform(sum.begin(), sum.end(), x2_.begin(), 
				 sum.begin(), std::plus<double>());
  return sum;
}

ConditDist*
JumpDist::Clone() const{
  return static_cast<ConditDist*>(new JumpDist(*this));
}

////////////////////////////////////////
// CONDITIONAL DISTRIBUTION INTERFACE //
////////////////////////////////////////

double 
JumpDist::ConditionalProbability(const std::vector<double>& x_,
                                 const std::vector<double>& x2_){
  if(!fPDF)
    throw NULLPointerAccessError("JumpDist::Probability",
                                 "Have you set the function?");
     
  return fPDF->operator()(Diff(x_, x2_));
}

std::vector<double> 
JumpDist::Sample(const std::vector<double>& x2_) const{
  if(!fPDF)
	throw NULLPointerAccessError("JumpDist::Integral",
                                 "Have you set the function?");
  std::vector<double> samp = fPDF->Sample();
  return Sum(samp, x2_);
}
double
JumpDist::Integral(const std::vector<double>& mins_,
									const std::vector<double>& maxs_,
									const std::vector<double>& x2_) const{
  if(!fPDF)
	throw NULLPointerAccessError("JumpDist::Integral",
                                 "Have you set the function?");
  
  return fPDF->Integral(Diff(maxs_, x2_), Diff(mins_, x2_));
}
									  

double 
JumpDist::Integral(double x2_) const{
 if(!fPDF)
	throw NULLPointerAccessError("JumpDist::Integral",
 								 "Have you set the function?");
 return fPDF->Integral();
}


/////////////////////////////
// FIT COMPONENT INTERFACE //
/////////////////////////////

void
JumpDist::MakeFittable(){
  if(!fPDF)
	throw NULLPointerAccessError("JumpDist::MakeFittable",
								   "Have you set the function?");
	fPDF->MakeFittable();
}

std::vector<std::string>
JumpDist::GetParameterNames() const{
  if(!fPDF)
	throw NULLPointerAccessError("JumpDist::GetParameterNames",
								   "Have you set the function?");
  return fPDF->GetParameterNames();
}


std::vector<double>
JumpDist::GetParameters() const{
  if(!fPDF)
	throw NULLPointerAccessError("JumpDist::GetParameters",
								   "Have you set the function?");
  return fPDF->GetParameters();
}

size_t
JumpDist::GetParameterCount() const{
  if(!fPDF)
	throw NULLPointerAccessError("JumpDist::GetParameterCount",
								 "Have you set the function?");
  return fPDF->GetParameterCount();
}


void
JumpDist::SetParameters(const std::vector<double>& params_){
  if(!fPDF)
	throw NULLPointerAccessError("JumpDist::SetParameters",
								 "Have you set the function?");
  fPDF->SetParameters(params_);
}
