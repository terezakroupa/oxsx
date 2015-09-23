#include <EventData.h>
#include <DataRepresentation.h>
#include <DataExceptions.h>

EventData::EventData(const std::vector<double>& obs_){
    fObservations = obs_;
}

std::vector<double> EventData::GetData() const{
    return fObservations;
}

std::vector<double> EventData::ToRepresentation(const DataRepresentation& rep_) const{
    size_t len = rep_.GetLength();
    std::vector<double> vals(len, 0); // can you do this better with iterators?
    try{
        for(size_t i = 0; i < len; i++)
            vals[i] = fObservations.at(rep_.GetIndex(i));
    }    
    catch(std::out_of_range&){
        throw RepresentationError("Data representation asked for indicies not in the data!");
    }

    return vals;
}
