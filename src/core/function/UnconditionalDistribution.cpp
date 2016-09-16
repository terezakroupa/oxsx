#include <UnconditionalDistribution.h>
#include <IntegrableFunction.h>
#include <Exceptions.h>
#include <algorithm>
#include <functional>

//////////////////////////////
// CONSTRUCTORS/DESTRUCTORS //
//////////////////////////////

UnconditionalDistribution::UnconditionalDistribution(IntegrableFunction* f_){
  if(fFunction)
	fFunction = static_cast<IntegrableFunction*>(f_->Clone());
  else
	fFunction = NULL;
}

UnconditionalDistribution::~UnconditionalDistribution(){
  delete fFunction;
}

UnconditionalDistribution::UnconditionalDistribution(const UnconditionalDistribution& other_){
  if(other_.fFunction)
	fFunction = static_cast<IntegrableFunction*>(other_.fFunction->Clone());
  else
	fFunction = NULL;
}

UnconditionalDistribution
UnconditionalDistribution::operator=(const UnconditionalDistribution& other_){
  if(other_.fFunction)
	fFunction = static_cast<IntegrableFunction*>(other_.fFunction->Clone());
  else
	fFunction = NULL;
}

std::vector<double>
UnconditionalDistribution::Diff(const std::vector<double>& x_, 
								const std::vector<double>& x2_) const{
  std::vector<double> diff = x_;
  std::transform(diff.begin(), diff.end(), x2_.begin(), 
				 diff.begin(), std::minus<double>());
  return diff;
}

ConditionalDistribution*
UnconditionalDistribution::Clone() const{
  return static_cast<ConditionalDistribution*>(new UnconditionalDistribution(*this));
}

////////////////////////////////////////
// CONDITIONAL DISTRIBUTION INTERFACE //
////////////////////////////////////////

double 
UnconditionalDistribution::ConditionalProbability(const std::vector<double>& x_,
												  const std::vector<double>& x2_){
  if(!fFunction)
    throw NULLPointerAccessError("UnconditionalDistribution::Probability",
                                 "Have you set the function?");
     
  return fFunction->operator()(Diff(x_, x2_));
}

std::vector<double> 
UnconditionalDistribution::Sample(const std::vector<double>& x2_) const{
  std::vector<double> samp = fFunction->Sample();
  return Diff(samp, x2_);
}
double
UnconditionalDistribution::Integral(const std::vector<double>& mins_,
									const std::vector<double>& maxs_,
									const std::vector<double>& x2_) const{
  if(!fFunction)
	throw NULLPointerAccessError("UnconditionalDistribution::Integral",
                                 "Have you set the function?");
  
  return fFunction->Integral(Diff(maxs_, x2_), Diff(mins_, x2_));
}
									  

double 
UnconditionalDistribution::Integral(double x2_) const{
 if(!fFunction)
	throw NULLPointerAccessError("UnconditionalDistribution::Integral",
 								 "Have you set the function?");
 return fFunction->Integral();
}


/////////////////////////////
// FIT COMPONENT INTERFACE //
/////////////////////////////

void
UnconditionalDistribution::MakeFittable(){
  if(!fFunction)
	throw NULLPointerAccessError("UnconditionalDistribution::MakeFittable",
								   "Have you set the function?");
	fFunction->MakeFittable();
}

std::vector<std::string>
UnconditionalDistribution::GetParameterNames() const{
  if(!fFunction)
	throw NULLPointerAccessError("UnconditionalDistribution::GetParameterNames",
								   "Have you set the function?");
  return fFunction->GetParameterNames();
}


std::vector<double>
UnconditionalDistribution::GetParameters() const{
  if(!fFunction)
	throw NULLPointerAccessError("UnconditionalDistribution::GetParameters",
								   "Have you set the function?");
  return fFunction->GetParameters();
}

size_t
UnconditionalDistribution::GetParameterCount() const{
  if(!fFunction)
	throw NULLPointerAccessError("UnconditionalDistribution::GetParameterCount",
								 "Have you set the function?");
  return fFunction->GetParameterCount();
}


void
UnconditionalDistribution::SetParameters(const std::vector<double>& params_){
  if(!fFunction)
	throw NULLPointerAccessError("UnconditionalDistribution::SetParameters",
								 "Have you set the function?");
  fFunction->SetParameters(params_);
}
