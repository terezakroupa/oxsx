#include <EventShift.h>
#include <EventData.h>
#include <Exceptions.h>

EventData
EventShift::operator()(const EventData& inEvent_){
    // pull out the relevant data point
    std::vector<double> obs = inEvent_.GetData();
    obs[fDataRep.GetIndex(0)] += GetShift();
    return EventData(obs);
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
