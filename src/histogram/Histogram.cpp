#include <Histogram.h>
#include <Exceptions.h>
#include <Formatter.hpp>
#include <Combinations.hpp>
#include <ContainerTools.hpp>
#include <iostream>
#include <set>
#include <algorithm>

Histogram::Histogram(const AxisCollection& axes_){
    SetAxes(axes_);
}

void 
Histogram::SetAxes(const AxisCollection& axes_){
    fAxes  = axes_;
    fNBins = fAxes.GetNBins();
    fNDims = fAxes.GetNDimensions();
    fBinContents.resize(fNBins, 0);
    
}

const AxisCollection& 
Histogram::GetAxes() const{
    return fAxes;
}

double 
Histogram::Integral() const{
    double sum = 0;
    for(size_t i = 0; i < fNBins; i++)
        sum += fBinContents[i];
    return sum;
}

void 
Histogram::Normalise(){
    double sum = Integral();
    for(size_t i = 0; i < fNBins; i++)
        fBinContents[i] /= sum;
}

void
Histogram::Scale(double s_){
    for(size_t i = 0; i < fNBins; i++)
        fBinContents[i] *= s_;
}

void 
Histogram::Fill(const std::vector<double>& vals_, double weight_){
    if(vals_.size() != fNDims)                             
        throw DimensionError("Histogram::Fill", fNDims, vals_.size());

    fBinContents[FindBin(vals_)] += weight_;
}

void 
Histogram::Fill(const std::map<std::string, double>& vals_, double weight_){
    try{
        Fill(ContainerTools::GetValues(vals_, GetAxisNames()), weight_);
    }
    catch(const std::out_of_range& e_){
        throw NotFoundError("Tried to fill a histogram with incomplete dictionary!");
    }
}


void 
Histogram::Fill(double vals_, double weight_){
    Fill(std::vector<double>(1, vals_), weight_);
}

size_t 
Histogram::FindBin(const std::vector<double>& vals_) const{
    return fAxes.FindBin(vals_);
    
}

double 
Histogram::GetBinContent(size_t bin_) const{
    if(bin_ > fNBins)
        throw NotFoundError(Formatter() 
                             << "Out of bounds bin access attempted on bin "
                             << bin_ <<  " !");
    return fBinContents[bin_];
}

void 
Histogram::AddBinContent(size_t bin_, double content_){
    if(bin_ > fNBins)
        throw NotFoundError(Formatter() 
                             << "Out of bounds bin access attempted on bin "
                             << bin_ <<  " !");
    fBinContents[bin_] += content_;
}

void 
Histogram::SetBinContent(size_t bin_, double content_){
    if(bin_ > fNBins)
        throw NotFoundError(Formatter()  << "Out of bounds bin access attempted on bin " << bin_ <<  " !");
    fBinContents[bin_] = content_;
}

size_t 
Histogram::GetNBins() const{
    return fNBins;
}

size_t 
Histogram::GetNDims() const{
  return fNDims;
}

void 
Histogram::Empty(){
    for(size_t i = 0; i < fNBins; i++)
        fBinContents[i] = 0;
}

size_t 
Histogram::FlattenIndices(const std::vector<size_t>& indices_) const{
    return fAxes.FlattenIndices(indices_);
}

std::vector<size_t> 
Histogram::UnpackIndices(size_t bin_) const{
    return fAxes.UnpackIndices(bin_);
}

std::vector<double> 
Histogram::GetBinContents() const{
    return fBinContents;
}
void 
Histogram::SetBinContents(const std::vector<double>& data_){
    if (data_.size() != fNBins)
        throw DimensionError("Histogram::SetBinContents", fNBins, 
                             data_.size());

    fBinContents = data_;
    fNBins = fBinContents.size();
}

std::vector<double>
Histogram::Means() const{
    std::vector<double> means(fNDims, 0);    
    for(size_t i = 0; i < fNBins; i++)
        for(size_t j = 0; j < fNDims; j++)
            means[j] += fBinContents.at(i) * fAxes.GetBinCentre(i, j);
    return means;
}

std::vector<double>
Histogram::Variances() const{
    std::vector<double> variances(fNDims, 0);

    for(size_t i = 0; i < fNBins; i++)
        for(size_t j = 0; j < fNDims; j++){
            double binCent = fAxes.GetBinCentre(i, j);
            variances[j] += binCent * binCent *  fBinContents.at(i);
        }
    
    

    std::vector<double> means = Means();
    for(size_t i = 0; i < fNDims; i++)
        variances[i] -= means.at(i) * means.at(i);

    return variances;
}

Histogram
Histogram::Marginalise(const std::vector<std::string>& axes_) const{
    std::vector<std::string> allAxisNames = fAxes.GetAxisNames();

    // check the pdf does contain the axes asked for
    for(size_t i = 0; i < axes_.size(); i++){

        if (std::find(allAxisNames.begin(), allAxisNames.end(), axes_.at(i)) == allAxisNames.end())
            throw NotFoundError(Formatter()
                                << "Histogram::Marginalise::Tried "
                                << "to project out non existent axis "
                                << axes_.at(i) << "!");
    }


    // work out which axis number corresponds to each name
    std::vector<size_t> indices;
    for(size_t i = 0; i < axes_.size(); i++)
        indices.push_back(fAxes.GetAxisIndex(axes_.at(i)));
        
    // Get the axes you are interested in, in the order requested
    AxisCollection newAxes;
    for(size_t i = 0;  i < axes_.size(); i++)
        newAxes.AddAxis(fAxes.GetAxis(axes_.at(i)));

    // New histogram
    Histogram marginalised(newAxes);

    std::vector<size_t> oldIndices(fNDims);
    std::vector<size_t> newIndices(axes_.size());
    size_t newBin = -1;

    // Now loop over the bins in old and fill new pdfs 
    for(size_t bin = 0; bin < fNBins; bin++){
        for(size_t i = 0; i < fNDims; i++)
            oldIndices[i] = fAxes.UnflattenIndex(bin, i);

        for(size_t i = 0; i < indices.size(); i++)
            newIndices[i] = oldIndices.at(indices.at(i));

        newBin = marginalised.FlattenIndices(newIndices);
        marginalised.AddBinContent(newBin, fBinContents.at(bin));
    }
    return marginalised;
}

Histogram
Histogram::Marginalise(const std::string& index_) const {
    return Marginalise(std::vector<std::string>(1, index_));
}


Histogram
Histogram::GetSlice(const std::map<std::string, size_t>& fixedBins_ ) const{
	const std::vector<std::string> allAxisNames = fAxes.GetAxisNames();

  // check the pdf does contain the axes and bins asked for
	for(std::map<std::string, size_t>::const_iterator it = fixedBins_.begin(); it!=fixedBins_.end(); it++){
		if (std::find(allAxisNames.begin(), allAxisNames.end(), it->first) == allAxisNames.end())
			throw NotFoundError(Formatter()
													<< "Histogram::GetSlice::Tried "
													<< "to get slice of non existent axis "
													<< it->first << "!");
	}

	// want a 1d slice, so check the dimensions
	if (fixedBins_.size() != fNDims-1)
		throw DimensionError("Histogram::GetSlice", fNDims-1, fixedBins_.size());
	
  //work out which axis is the slice in (i.e. the not fixed one)
	std::string newAxisName;
	size_t newAxisIndex;
	std::vector<size_t> sliceIndices(fNDims);
	
	for(std::vector<std::string>::const_iterator it = allAxisNames.begin(); it!=allAxisNames.end(); it++){
		if(fixedBins_.find(*it) == fixedBins_.end()){
			//this is the axis we want the slice in
			newAxisName = *it;
			newAxisIndex = fAxes.GetAxisIndex(*it);
		}else{
			//record the indices for the fixed bins in other dimensions
			sliceIndices[fAxes.GetAxisIndex(*it)] = fixedBins_.at(*it);
			std::cout<< "Histogram::GetSlice sliceIndices: axis index " << fAxes.GetAxisIndex(*it) << " bin " << fixedBins_.at(*it) << std::endl;
		}
	}


	std::cout<< "Histogram::GetSlice newAxisName: " << newAxisName << std::endl;
	std::cout<< "Histogram::GetSlice newAxisIndex: " << newAxisIndex << std::endl;
	
 
	// New histogram
	AxisCollection newAxes;
	newAxes.AddAxis(fAxes.GetAxis(newAxisIndex));
	Histogram slice(newAxes);


	// loop over bins in the slice histo and fill it
	for(size_t bin = 0; bin < newAxes.GetNBins(); bin++){
		sliceIndices[newAxisIndex] = bin;
		size_t oldGlobalBin = fAxes.FlattenIndices(sliceIndices);
		std::cout<< "Histogram::GetSlice oldGlobalBin: " << oldGlobalBin << std::endl;
		std::cout<< "Histogram::GetSlice newBin: " <<  bin << std::endl;
		std::cout<< "Histogram::GetSlice bin content: " <<  fBinContents.at(oldGlobalBin) << std::endl;
		slice.AddBinContent(bin, fBinContents.at(oldGlobalBin));
	}
    return slice;

}


double
Histogram::GetBinLowEdge(size_t bin_, size_t index_) const{
    return fAxes.GetBinLowEdge(bin_, index_);
}

double
Histogram::GetBinHighEdge(size_t bin_, size_t index_) const{
    return fAxes.GetBinHighEdge(bin_, index_);
}

double
Histogram::GetBinCentre(size_t bin_, size_t index_) const{
    return fAxes.GetBinCentre(bin_, index_);
}

void
Histogram::Add(const Histogram& other_, double weight_){
    if(other_.GetAxes() != GetAxes())
        throw ValueError(Formatter() << "Histogram::Add can't add histograms with different binning definitions!");
    
    for(size_t i = 0; i < GetNBins(); i++)
        AddBinContent(i, other_.GetBinContent(i) * weight_);
}


void
Histogram::Multiply(const Histogram& other_){
    if(other_.GetAxes() != GetAxes())
        throw ValueError(Formatter() << "Histogram::Add can't add histograms with different binning definitions!");
    
    for(size_t i = 0; i < GetNBins(); i++)
        SetBinContent(i, GetBinContent(i) * other_.GetBinContent(i));
}


void
Histogram::Divide(const Histogram& other_){
    if(other_.GetAxes() != GetAxes())
        throw ValueError(Formatter() << "Histogram::Add can't add histograms with different binning definitions!");
    
    for(size_t i = 0; i < GetNBins(); i++)
        SetBinContent(i, GetBinContent(i) / other_.GetBinContent(i));
}

std::vector<std::string>
Histogram::GetAxisNames() const{
    return fAxes.GetAxisNames();
}

size_t
Histogram::GetAxisIndex(const std::string& name_) const{
    return fAxes.GetAxisIndex(name_);
}
