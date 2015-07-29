#include "DataHandler.h"

std::vector<std::vector<size_t> > DataHandler::fReps;
std::vector<size_t> DataHandler::fRepLens;

DataHandler::DataHandler(const std::vector<double>& obs_){
    fObservations = obs_;
}

std::vector<double> DataHandler::GetData() const{
    return fObservations;
}

std::vector<double> DataHandler::ToRepresentation(size_t iRep_) const{
    std::vector<double> rep(fRepLens.at(iRep_), 0); // can you do this better with iterators
    for(size_t i = 0; i < fRepLens.at(iRep_); i++ )
        rep[i] = fObservations.at(fReps[iRep_][i]);
    return rep;
}

void DataHandler::AddRepresentation(const std::vector<size_t>& indicies_){
    fReps.push_back(indicies_);
    fRepLens.push_back(indicies_.size());
}
