#include <DataRepresentation.h>
#include <DataExceptions.h>

DataRepresentation::DataRepresentation(const std::vector<size_t>& indicies_){
    SetIndicies(indicies_);
}

DataRepresentation::DataRepresentation(size_t index_){
    SetIndicies(std::vector<size_t>(1, index_));
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

    // build inverse map
    fInverse.resize(0);
    for(size_t i = 0; i < fIndicies.size(); i++)
        fInverse.push_back(std::pair<size_t,size_t>(fIndicies.at(i), i));
    
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

size_t
DataRepresentation::GetDataIndexPos(size_t dataIndex_) const{
    for(size_t i = 0; i < fInverse.size(); i++){
        if (dataIndex_ == fInverse.at(i).first)
            return fInverse.at(i).second;
    }
    throw RepresentationError("Incompatible data representation"); // 
}

std::vector<size_t> 
DataRepresentation::GetRelativeIndicies(const DataRepresentation& otherRep_) const{
    // given a longer represetation containing the indicies of this rep, where are the shared indicies
    // in the big rep

    if(otherRep_.GetLength() < fLen)
        throw RepresentationError("Tried to take relatice indicies in compatible representations ");
        
    std::vector<size_t> relativeIndicies(fIndicies.size(), 0);
    for(size_t i = 0; i < fIndicies.size(); i++)
        relativeIndicies[i] = GetDataIndexPos(otherRep_.fIndicies.at(i));
    
    return relativeIndicies;
} 
