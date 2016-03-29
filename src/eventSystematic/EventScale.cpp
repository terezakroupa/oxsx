#include <EventScale.h>
#include <PdfExceptions.h>
#include <DataExceptions.h>
#include <EventData.h>
#include <stdexcept>

EventScale::EventScale(){
    fParams = std::vector<double>(1, 1);
}

EventData
EventScale::operator()(const EventData& inEvent_){
    // pull out the relevant data point
    std::vector<double> obs = inEvent_.GetData();
    obs[fDataRep.GetIndex(0)] *= GetScale();
    return EventData(obs);
}

void
EventScale::SetParameters(const std::vector<double>& params_){
    if(params_.size() != 1)
        throw DimensionError("EventScale::SetParamters() called with more than one argument! There is only the size of shift.");
    SetScale(params_.at(0));
}

void
EventScale::SetParameter(size_t index_, double val_){
    if (index_ != 0)
        throw DimensionError("EventScale::SetParamter() called on non-existent argument! There is only the size of shift.");

    SetScale(val_);
}

double
EventScale::GetParameter(size_t index_) const{
    if (index_ != 0)
        throw DimensionError("EventScale::GetParameter() called on non-existent argument! There is only the size of shift.");
    
    return GetScale();                    
}

void
EventScale::SetScale(double val_){
    fParams.clear();
    fParams.push_back(val_);
}

double 
EventScale::GetScale() const{
    try{
        return fParams.at(0);
    }

    // FIXME, pdfExpcetopn 
    catch(const std::out_of_range& e){
        throw PdfException("EventScale::GetScale() called, but shift not yet set");
    }
}

void
EventScale::SetDataRep(const DataRepresentation& rep_){
    if (rep_.GetLength() != 1)
        throw RepresentationError("EventScale::SetDataRep tried to set data rep to a rep with more than one index! shifts are 1D");
    fDataRep = rep_;
}
