#include <EventShift.h>
#include <PdfExceptions.h>
#include <DataExceptions.h>
#include <EventData.h>
#include <stdexcept>

EventData
EventShift::operator()(const EventData& inEvent_){
    // pull out the relevant data point
    std::vector<double> obs = inEvent_.GetData();
    obs[fDataRep.GetIndex(0)] += GetShift();
    return EventData(obs);
}

void
EventShift::SetParameters(const std::vector<double>& params_){
    if(params_.size() != 1)
        throw DimensionError("EventShift::SetParamters() called with more than one argument! There is only the size of shift.");
    SetShift(params_.at(0));
}

void
EventShift::SetParameter(size_t index_, double val_){
    if (index_ != 0)
        throw DimensionError("EventShift::SetParamter() called on non-existent argument! There is only the size of shift.");

    SetShift(val_);
}

double
EventShift::GetParameter(size_t index_) const{
    if (index_ != 0)
        throw DimensionError("EventShift::GetParameter() called on non-existent argument! There is only the size of shift.");
    
    return GetShift();                    
}

void
EventShift::SetShift(double val_){
    fParams.clear();
    fParams.push_back(val_);
}

double 
EventShift::GetShift() const{
    try{
        return fParams.at(0);
    }

    // FIXME, pdfExpcetopn 
    catch(const std::out_of_range& e){
        throw PdfException("EventShift::GetShift() called, but shift not yet set");
    }
}

void
EventShift::SetDataRep(const DataRepresentation& rep_){
    if (rep_.GetLength() != 1)
        throw RepresentationError("EventShift::SetDataRep tried to set data rep to a rep with more than one index! shifts are 1D");
    fDataRep = rep_;
}
