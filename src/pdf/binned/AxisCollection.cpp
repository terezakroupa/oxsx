#include "AxisCollection.h"
#include <iostream>
size_t AxisCollection::GetNBins() const {return fNBins;}
size_t AxisCollection::GetNDimensions() const {return fNDimensions;}

const PdfAxis& AxisCollection::GetAxis(size_t axisIndex_) const{
    return fAxes.at(axisIndex_);
}

void AxisCollection::CountBins(){
    fNBins = 1;
    for(size_t i = 0; i < fNDimensions; i++)
        fNBins *= fAxisNbins[i];
}

void AxisCollection::AddAxis(const PdfAxis& axis_){
    if (HasAxis(axis_.GetName())){
        std::cout << "cant add axis " << axis_.GetName() << " already has an axis by that name!" 
                  << std::endl;
        return;
    }
        
    fAxes.push_back(axis_);
    fAxisNbins.push_back(axis_.GetNBins());
    fNDimensions++;
    CountBins();
}

void AxisCollection::AddAxes(const std::vector<PdfAxis>& axes_){
    for(size_t i = 0; i < axes_.size(); i++)
        AddAxis(axes_[i]);
}

size_t AxisCollection::FlattenIndicies(const std::vector<size_t>& indicies_) const{
    if(indicies_.size() != fNDimensions)
        throw DimensionError("Can't flatten! wrong number of indicies");
    size_t index = indicies_.back();
    for (size_t i = 0; i < fNDimensions-1; i++){
        size_t x = indicies_[i];
        for(size_t j = i+1; j < fNDimensions; j++)
            x *= fAxisNbins[j];
        index += x;
    }
    return index;
}


size_t AxisCollection::FindBin(const std::vector<double>& vals_) const{
    if (vals_.size() != fNDimensions)
        throw DimensionError("Can't find bin! wrong number of vals");

    std::vector<size_t> indicies(fNDimensions, 0);
    for (size_t i = 0; i < fNDimensions; i++)
        indicies[i] = fAxes.at(i).FindBin(vals_[i]);

    return FlattenIndicies(indicies);
}

size_t AxisCollection::UnflattenIndex(size_t index_, size_t dim_) const{
    if (index_ >= fNBins)
        throw OutOfBoundsError("index out of bounds");
    size_t x =1;
    for (size_t i = dim_+1 ; i < fNDimensions; i++ )
        x *= fAxisNbins[i];
    return (index_/x) % fAxisNbins[dim_];
}

std::vector<size_t> AxisCollection::UnpackIndicies(size_t index_) const{
    std::vector<size_t> indicies(fNDimensions, 0);
    for(size_t i = 0; i < fNDimensions; i++)
        indicies[i] = UnflattenIndex(index_, i);
    return indicies;
}

bool AxisCollection::HasAxis(const std::string& name_){
    for(size_t i = 0; i < fNDimensions; i++)
        if(name_ == fAxes[i].GetName())
            return true;
    return false;
}
