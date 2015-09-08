#include <DataHandler.h>
#include <DataRepresentation.h>

DataHandler::DataHandler(const std::vector<double>& obs_){
    fObservations = obs_;
}

std::vector<double> DataHandler::GetData() const{
    return fObservations;
}

std::vector<double> DataHandler::ToRepresentation(const DataRepresentation& rep_) const{
    size_t len = rep_.GetLength();
    std::vector<double> vals(len, 0); // can you do this better with iterators?
    for(size_t i = 0; i < len; i++)
        vals[i] = fObservations.at(rep_.GetIndex(i));
    return vals;
}


