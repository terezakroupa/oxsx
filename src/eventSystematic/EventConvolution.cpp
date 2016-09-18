#include <EventConvolution.h>
#include <IntegrableFunction.h>
#include <JumpDistribution.h>
#include <Exceptions.h>
#include <Rand.h>
#include <EventData.h>
#include <iostream>

/////////////////////////////
// CONSTRUCTORS/DESTRUCTOR //
/////////////////////////////

EventConvolution::~EventConvolution(){
  delete fDist;
}

EventConvolution::EventConvolution(const EventConvolution& other_){
  if(other_.fDist)
	fDist = other_.fDist -> Clone();
  else
  	fDist = NULL;
  fDataRep = other_.fDataRep;
}

EventConvolution
EventConvolution::operator=(const EventConvolution& other_){ 
  if(other_.fDist)
  	fDist = other_.fDist -> Clone();
  else								   
  	fDist = NULL;
  fDataRep = other_.fDataRep;
  return *this;
}

/////////////
// Get/Set //
/////////////

void
EventConvolution::SetFunction(IntegrableFunction* f_){
  if(!f_)
	fDist = NULL;

  else{
	if(f_->GetNDims() != 1)
	  throw DimensionError("EventConvolution::SetFunction", 1, 
						   f_->GetNDims(), "Only implemented for 1D functions");
	fDist = static_cast<ConditionalDistribution*>(new JumpDistribution(f_));
  }	
}

void
EventConvolution::SetConditionalDistribution(ConditionalDistribution* c_){
  if(!c_)
	fDist = NULL;
  else
	fDist  = c_->Clone();
}

/////////////////////////////////////////////////////////////////////////////
// FIT COMPONENT INTERFACE : just forward the call to the underlying funcn //
/////////////////////////////////////////////////////////////////////////////

void
EventConvolution::MakeFittable(){
  if(!fDist)
	throw NULLPointerAccessError("EventConvolution::MakeFittable", 
								 "Have you set the function?");
  fDist->MakeFittable();
}

std::vector<std::string> 
EventConvolution::GetParameterNames() const{
  if(!fDist)
	throw NULLPointerAccessError("EventConvolution::GetParameterNames", 
								 "Have you set the sampling function?");
  return fDist->GetParameterNames();
}

std::vector<double> 
EventConvolution::GetParameters() const{
  if(!fDist)
	throw NULLPointerAccessError("EventConvolution::GetParameters", 
								 "Have you set the sampling function?");
  return fDist->GetParameters();
}

size_t
EventConvolution::GetParameterCount() const{
  if(!fDist)
	throw NULLPointerAccessError("EventConvolution::GetParameterCount", 
								 "Have you set the sampling function?");
  return fDist->GetParameterCount();
}

void
EventConvolution::SetParameters(const std::vector<double>& params_){
  if(!fDist)
	throw NULLPointerAccessError("EventConvolution::SetParameters", 
								 "Have you set the sampling function?");
  return fDist->SetParameters(params_);
}


// Event Systematic Interface
EventData
EventConvolution::operator()(const EventData& event_){
  if(!fDist)
	throw NULLPointerAccessError("EventConvolution::operator()", 
								 "Have you set the sampling function?");

  double correction = fDist->Sample(event_.ToRepresentation(fDataRep)).at(0);

  std::vector<double> obs = event_.GetData();
  double relevantOb = obs.at(fDataRep.GetIndex(0));
  obs[fDataRep.GetIndex(0)] = relevantOb + correction;
  return EventData(obs);
}
