#include <DataRepresentation.h>


DataRepresentation::DataRepresentation(const std::vector<size_t>& indicies_){
    SetIndicies(indicies_);
}

DataRepresentation::DataRepresentation(const DataRepresentation& other_){
    fName = other_.fName;
    SetIndicies(other_.fIndicies);
}


std::vector<size_t>
DataRepresentation::GetIndicies() const {return fIndicies;}

void 
DataRepresentation::SetIndicies(const std::vector<size_t>& indicies_)  {
    fIndicies = indicies_;
    fLen = indicies_.size();
}

std::string
DataRepresentation::GetName() const {return fName;}

void
DataRepresentation::SetName(const std::string& name_) {fName = name_;}

// FIXME -  needs bounds handling!
size_t
DataRepresentation::GetIndex(size_t indexNum_) const{return fIndicies.at(indexNum_);}

size_t
DataRepresentation::GetLength() const {return fLen;}
