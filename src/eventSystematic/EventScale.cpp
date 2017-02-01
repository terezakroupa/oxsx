#include <EventScale.h>
#include <Exceptions.h>
#include <Event.h>
#include <string>
#include <Formatter.hpp>

Event
EventScale::operator()(const Event& inEvent_){
    // pull out the relevant data point
    std::vector<double> obs = inEvent_.GetData();
    obs[fObservables.GetIndex(0)] *= GetScale();
    return Event(obs);
}

void 
EventScale::SetScale(double scale_){
    if(scale_ <= 0)
        throw ValueError(Formatter() << "Tried to set EventScale systematic scale to " << scale_ << " - must be >= 0");
    fScale = scale_;
}

double
EventScale::GetScale() const{
    return fScale;
}


// Fit Component Interface  
std::vector<std::string>
EventScale::GetParameterNames() const{
    return std::vector<std::string>(1, fScaleName);
}

std::vector<double>
EventScale::GetParameters() const{
    return std::vector<double>(1, fScale);
}


size_t
EventScale::GetParameterCount() const{
    return 1;
}

void
EventScale::SetParameters(const std::vector<double>& params_){
    if(params_.size() != 1)
        throw ParameterCountError("Event Scale", 1, params_.size());
    SetScale(params_.at(0));
}

double
EventScale::GetParameter(const std::string& name_) const{
    if(name_ != fScaleName)
        throw NotFoundError(Formatter() << "EventScale::No parameter called " << name_ << ", only" << fScaleName);
    return fScale;
}

void
EventScale::SetParameter(const std::string& name_, double val_){
    if(name_ != fScaleName)
        throw NotFoundError(Formatter() << "EventScale::No parameter called " << name_ << ", only " << fScaleName << ".");
    fScale = val_;
}

void 
EventScale::SetParameterNames(const std::vector<std::string>& names_){
    if(names_.size() != 1)
        throw DimensionError("EventScale::SetParameterNames", 1, names_.size(),
                             ", there's only one parameter");
    fScaleName = names_.at(0);
}


