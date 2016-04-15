#include <EventData.h>
#include <DataRepresentation.h>
#include <DataExceptions.h>
#include <PdfExceptions.h>

EventData::EventData(const std::vector<double>& obs_){
    fObservations = obs_;
    fNObservables  = obs_.size(); 
}

std::vector<double> 
EventData::GetData() const{
    return fObservations;
}

double
EventData::GetDatum(size_t index_) const{
    try{
        return fObservations.at(index_);
    }

    catch(const std::out_of_range& e_){
        throw DimensionError("EventData::Attempted access on non-existent observable");
    }
}

std::vector<double> 
EventData::ToRepresentation(const DataRepresentation& rep_) const{
    size_t nObs = rep_.GetNObservables();

    if (!nObs)
        throw RepresentationError("Event Data queried with empty representation!");

    std::vector<double> vals(nObs, 0); // can you do this better with iterators?
    try{
        for(size_t i = 0; i < nObs; i++)
            vals[i] = fObservations.at(rep_.GetIndex(i));
    }    
    catch(std::out_of_range&){
        throw RepresentationError("Data representation asked for indicies not in the data!");
    }

    return vals;
}
