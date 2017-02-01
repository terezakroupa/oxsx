#include <EventShift.h>
#include <Event.h>
#include <Exceptions.h>

Event
EventShift::operator()(const Event& inEvent_){
    // pull out the relevant data point
    std::vector<double> obs = inEvent_.GetData();
    obs[fObservables.GetIndex(0)] += GetShift();
    return Event(obs);
}

void
EventShift::SetShift(double val_){
    fShift = val_;
}

double 
EventShift::GetShift() const{
    return fShift;
}

// Fit Component Interface
std::vector<std::string>
EventShift::GetParameterNames() const{
    return std::vector<std::string>(1, Formatter() << "Shift systematic on parameter");
}

std::vector<double>
EventShift::GetParameters() const{
    return std::vector<double>(1, fShift);
}

size_t
EventShift::GetParameterCount() const{
    return 1;
}

void
EventShift::SetParameters(const std::vector<double>& params_){
    if(params_.size() != 1)
        throw ParameterCountError("Event Shift", 1, params_.size());
    SetShift(params_.at(0));
}


double
EventShift::GetParameter(const std::string& name_) const{
    if(name_ != fShiftName)
        throw NotFoundError(Formatter() << "EventShift::No parameter called " << name_ \
                            << ", only" << fShiftName);
    return fShift;
}

void
EventShift::SetParameter(const std::string& name_, double val_){
    if(name_ != fShiftName)
        throw NotFoundError(Formatter() << "EventShift::No parameter called " << name_ \
                            << ", only " << fShiftName << ".");
    fShift = val_;
}

void
EventShift::SetParameterNames(const std::vector<std::string>& names_){
    if(names_.size() != 1)
        throw DimensionError("EventShift::SetParameterNames", 1, names_.size(),
                             ", there's only one parameter");
    fShiftName = names_.at(0);
}
