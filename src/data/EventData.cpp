#include <EventData.h>
#include <DataRepresentation.h>

EventData::EventData(const std::vector<double>& obs_){
    fObservations = obs_;
}

std::vector<double> EventData::GetData() const{
    return fObservations;
}

std::vector<double> EventData::ToRepresentation(const DataRepresentation& rep_) const{
    size_t len = rep_.GetLength();
    std::vector<double> vals(len, 0); // can you do this better with iterators?
    for(size_t i = 0; i < len; i++)
        vals[i] = fObservations.at(rep_.GetIndex(i));
    return vals;
}


