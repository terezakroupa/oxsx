#include <EventScale.h>
#include <Exceptions.h>
#include <EventData.h>
#include <string>
#include <Formatter.hpp>

EventData
EventScale::operator()(const EventData& inEvent_){
    // pull out the relevant data point
    std::vector<double> obs = inEvent_.GetData();
    obs[fDataRep.GetIndex(0)] *= GetScale();
    return EventData(obs);
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
    return std::vector<std::string>(1, Formatter() << "Scale systematic on parameter");
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

