#include <AxisCollection.h>
#include <iostream>
#include <PdfExceptions.h>

size_t AxisCollection::GetNBins() const {return fNBins;}
size_t AxisCollection::GetNDimensions() const {return fNDimensions;}

const PdfAxis& AxisCollection::GetAxis(size_t axisIndex_) const{
    try {
        return fAxes.at(axisIndex_);
    }

    catch (const std::out_of_range& e_){
        throw DimensionError(e_.what());
    }
}

void AxisCollection::CountBins(){
    if (!fNDimensions)
        fNBins = 0;

    else{
        fNBins = 1;
        for(size_t i = 0; i < fNDimensions; i++)
            fNBins *= fAxisNbins[i];
    }
}

void AxisCollection::AddAxis(const PdfAxis& axis_){
    if (HasAxis(axis_.GetName())){
        throw DimensionError("Can't add axis " + axis_.GetName() + " already exists!"); 
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

std::vector<double> 
AxisCollection::GetBinLowEdges(size_t bin_) const{

    if(bin_ > fNBins)
        throw OutOfBoundsError("Bin Edge call on out of bounds bin!");

    std::vector<size_t> indicies = UnpackIndicies(bin_);
    std::vector<double> lowEdges(fNDimensions, 0);

    for(size_t i = 0; i <fNDimensions; i++){
        lowEdges[i] = fAxes[i].GetBinLowEdge(indicies.at(i));
    }
    return lowEdges;
}

std::vector<double> 
AxisCollection::GetBinHighEdges(size_t bin_) const{

    if(bin_ > fNBins)
        throw OutOfBoundsError("Bin Edge call on out of bounds bin!");

    std::vector<size_t> indicies = UnpackIndicies(bin_);
    std::vector<double> lowEdges(fNDimensions, 0);

    for(size_t i = 0; i <fNDimensions; i++){
        lowEdges[i] = fAxes[i].GetBinHighEdge(indicies.at(i));
    }
    return lowEdges;
}

std::vector<double>
AxisCollection::GetBinCentre(size_t bin_) const{

    if(bin_ > fNBins)
        throw OutOfBoundsError("Bin Edge call on out of bounds bin!");

    std::vector<size_t> indicies = UnpackIndicies(bin_);
    std::vector<double> centre(fNDimensions, 0);

    for(size_t i = 0; i <fNDimensions; i++){
        centre[i] = fAxes[i].GetBinCentre(indicies.at(i));
    }
    return centre;
}
