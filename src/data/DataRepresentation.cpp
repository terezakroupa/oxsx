#include <DataRepresentation.h>

std::vector<size_t>
DataRepresentation::GetIndicies() const {return fIndicies;}

void 
DataRepresentation::SetIndicies(const std::vector<size_t>& indicies_)  {fIndicies = indicies_;}

std::string
DataRepresentation::GetName() const {return fName;}

void
DataRepresentation::SetName(const std::string& name_) {fName = name_;}

DataRepresentation::DataRepresentation(const DataRepresentation& other_){
    fName = other_.fName;
    fIndicies = other_.fIndicies;
}
