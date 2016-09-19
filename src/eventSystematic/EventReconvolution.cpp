#include <EventReconvolution.h>
#include <Event.h>
#include <Formatter.hpp>
#include <Exceptions.h>
#include <iostream>

Event
EventReconvolution::operator()(const Event& event_){
    std::vector<double> obs = event_.GetData();
    double relevantOb = obs.at(fObservables.GetIndex(0));
    double truthVal   = obs.at(fObservables.GetIndex(1));

    obs[fObservables.GetIndex(0)] = truthVal + fCorrection * (relevantOb - truthVal);
    return Event(obs);
}

void
EventReconvolution::SetCorrection(double correction_){
    if(correction_ < 0)
        throw ValueError(Formatter() << "Tried to set Reconvolution systematic correction factor to " << correction_ << " - must be >= 0");
    fCorrection = correction_;
}
    

// Fit Component Interface
std::vector<std::string>
EventReconvolution::GetParameterNames() const{
    return std::vector<std::string>(1, Formatter() << "Reconvolution systematic on parameter");
}

std::vector<double>
EventReconvolution::GetParameters() const{
    return std::vector<double>(1, fCorrection);
}

size_t
EventReconvolution::GetParameterCount() const{
    return 1;
}


void
EventReconvolution::SetParameters(const std::vector<double>& params_){
    if(params_.size() != 1)
        throw ParameterCountError("Event Reconvolution", 1, params_.size());
    SetCorrection(params_.at(0));
}
