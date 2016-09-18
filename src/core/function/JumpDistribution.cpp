#include <JumpDistribution.h>
#include <IntegrableFunction.h>
#include <Exceptions.h>
#include <algorithm>
#include <functional>

//////////////////////////////
// CONSTRUCTORS/DESTRUCTORS //
//////////////////////////////

JumpDistribution::JumpDistribution(IntegrableFunction* f_){
  if(f_)
	fFunction = static_cast<IntegrableFunction*>(f_->Clone());
  
  else
	fFunction = NULL;  
}

JumpDistribution::~JumpDistribution(){
  delete fFunction;
}

JumpDistribution::JumpDistribution(const JumpDistribution& other_){
  if(other_.fFunction)
	fFunction = static_cast<IntegrableFunction*>(other_.fFunction->Clone());
  else
	fFunction = NULL;
}

JumpDistribution
JumpDistribution::operator=(const JumpDistribution& other_){
  if(other_.fFunction)
	fFunction = static_cast<IntegrableFunction*>(other_.fFunction->Clone());
  else
	fFunction = NULL;
  return *this;
}

std::vector<double>
JumpDistribution::Diff(const std::vector<double>& x_, 
								const std::vector<double>& x2_) const{
  std::vector<double> diff = x_;
  std::transform(diff.begin(), diff.end(), x2_.begin(), 
				 diff.begin(), std::minus<double>());
  return diff;
}

std::vector<double>
JumpDistribution::Sum(const std::vector<double>& x_, 
							   const std::vector<double>& x2_) const{
  std::vector<double> sum = x_;
  std::transform(sum.begin(), sum.end(), x2_.begin(), 
				 sum.begin(), std::plus<double>());
  return sum;
}

ConditionalDistribution*
JumpDistribution::Clone() const{
  return static_cast<ConditionalDistribution*>(new JumpDistribution(*this));
}

////////////////////////////////////////
// CONDITIONAL DISTRIBUTION INTERFACE //
////////////////////////////////////////

double 
JumpDistribution::ConditionalProbability(const std::vector<double>& x_,
												  const std::vector<double>& x2_){
  if(!fFunction)
    throw NULLPointerAccessError("JumpDistribution::Probability",
                                 "Have you set the function?");
     
  return fFunction->operator()(Diff(x_, x2_));
}

std::vector<double> 
JumpDistribution::Sample(const std::vector<double>& x2_) const{
  if(!fFunction)
	throw NULLPointerAccessError("JumpDistribution::Integral",
                                 "Have you set the function?");
  std::vector<double> samp = fFunction->Sample();
  return Sum(samp, x2_);
}
double
JumpDistribution::Integral(const std::vector<double>& mins_,
									const std::vector<double>& maxs_,
									const std::vector<double>& x2_) const{
  if(!fFunction)
	throw NULLPointerAccessError("JumpDistribution::Integral",
                                 "Have you set the function?");
  
  return fFunction->Integral(Diff(maxs_, x2_), Diff(mins_, x2_));
}
									  

double 
JumpDistribution::Integral(double x2_) const{
 if(!fFunction)
	throw NULLPointerAccessError("JumpDistribution::Integral",
 								 "Have you set the function?");
 return fFunction->Integral();
}


/////////////////////////////
// FIT COMPONENT INTERFACE //
/////////////////////////////

void
JumpDistribution::MakeFittable(){
  if(!fFunction)
	throw NULLPointerAccessError("JumpDistribution::MakeFittable",
								   "Have you set the function?");
	fFunction->MakeFittable();
}

std::vector<std::string>
JumpDistribution::GetParameterNames() const{
  if(!fFunction)
	throw NULLPointerAccessError("JumpDistribution::GetParameterNames",
								   "Have you set the function?");
  return fFunction->GetParameterNames();
}


std::vector<double>
JumpDistribution::GetParameters() const{
  if(!fFunction)
	throw NULLPointerAccessError("JumpDistribution::GetParameters",
								   "Have you set the function?");
  return fFunction->GetParameters();
}

size_t
JumpDistribution::GetParameterCount() const{
  if(!fFunction)
	throw NULLPointerAccessError("JumpDistribution::GetParameterCount",
								 "Have you set the function?");
  return fFunction->GetParameterCount();
}


void
JumpDistribution::SetParameters(const std::vector<double>& params_){
  if(!fFunction)
	throw NULLPointerAccessError("JumpDistribution::SetParameters",
								 "Have you set the function?");
  fFunction->SetParameters(params_);
}
