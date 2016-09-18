#include <BinnedPhysDist.h>
#include <Exceptions.h>
#include <Combinations.hpp>

BinnedPhysDist::BinnedPhysDist(const AxisCollection& axes_){
    fHistogram.SetAxes(axes_);
}

BinnedPhysDist::BinnedPhysDist(const Histogram& histo_){
    fHistogram = histo_;
}

void
BinnedPhysDist::SetDataRep(const DataRepresentation& rep_){
    fDataRep = rep_;
}

DataRepresentation
BinnedPhysDist::GetDataRep() const {
    return fDataRep;
}

const Histogram&
BinnedPhysDist::GetHistogram() const{
    return fHistogram;
}

void
BinnedPhysDist::SetHistogram(const Histogram& hist_){
    fHistogram = hist_;
}

void 
BinnedPhysDist::Fill(const EventData& data_, double weight_){
    try{
        fHistogram.Fill(data_.ToRepresentation(fDataRep), weight_);
    }
    catch (const DimensionError& e_){
        throw RepresentationError(std::string("Representation in compatible with pdf ") + e_.what());
    }
}

size_t 
BinnedPhysDist::FindBin(const EventData& data_) const{
    try{
        return fHistogram.FindBin(data_.ToRepresentation(fDataRep));    
    }
    catch (const DimensionError& e_){
        throw RepresentationError(std::string("Representation in compatible with pdf ") + e_.what());
    }    
}

PhysDist* 
BinnedPhysDist::Clone() const{
    return static_cast<PhysDist*>(new BinnedPhysDist(*this));
}


//////////////////////////////////////////////////////////////////////////////////////////
// All methods below this line just forward the call to the underlying histogram object //
//////////////////////////////////////////////////////////////////////////////////////////

void 
BinnedPhysDist::SetAxes(const AxisCollection& axes_){
    fHistogram.SetAxes(axes_);

}

const AxisCollection& 
BinnedPhysDist::GetAxes() const{
    return fHistogram.GetAxes();
}

double 
BinnedPhysDist::Probability(const std::vector<double>& vals_) const{
    return fHistogram.GetBinContent(fHistogram.FindBin(vals_))/fHistogram.Integral();
}

double
BinnedPhysDist::Probability(const EventData& oberservations_) const{
    try{
        return Probability(oberservations_.ToRepresentation(fDataRep));
    }

    catch(const RepresentationError& e_){
        throw RepresentationError("BinnedPhysDist::Probability() failed with  " 
                                  + std::string(e_.what()) 
                                  + " is the rep set correctly?");
    }
}

double 
BinnedPhysDist::Integral() const{
    return fHistogram.Integral();
}

void 
BinnedPhysDist::Normalise(){
    fHistogram.Normalise();
}

void
BinnedPhysDist::Scale(double s_){
    fHistogram.Scale(s_);
}

void 
BinnedPhysDist::Fill(const std::vector<double>& vals_, double weight_){
    fHistogram.Fill(vals_, weight_);
}


void 
BinnedPhysDist::Fill(double vals_, double weight_){
    fHistogram.Fill(vals_, weight_);
}

size_t 
BinnedPhysDist::FindBin(const std::vector<double>& vals_) const{
    return fHistogram.FindBin(vals_);
    
}

double 
BinnedPhysDist::GetBinContent(size_t bin_) const{
    return fHistogram.GetBinContent(bin_);
}

void 
BinnedPhysDist::AddBinContent(size_t bin_, double content_){
    fHistogram.AddBinContent(bin_, content_);
}

void 
BinnedPhysDist::SetBinContent(size_t bin_, double content_){
    fHistogram.SetBinContent(bin_, content_);
}

size_t 
BinnedPhysDist::GetNBins() const{
    return fHistogram.GetNBins();
}

unsigned
BinnedPhysDist::GetNDims() const{
    return fHistogram.GetNDims();
}

void 
BinnedPhysDist::Empty(){
    fHistogram.Empty();
}

size_t 
BinnedPhysDist::FlattenIndices(const std::vector<size_t>& indices_) const{
    return fHistogram.FlattenIndices(indices_);
}

std::vector<size_t> 
BinnedPhysDist::UnpackIndices(size_t bin_) const{
    return fHistogram.UnpackIndices(bin_);
}

std::vector<double> 
BinnedPhysDist::GetBinContents() const{
    return fHistogram.GetBinContents();
}
void 
BinnedPhysDist::SetBinContents(const std::vector<double>& data_){
    return fHistogram.SetBinContents(data_);
}

std::vector<double>
BinnedPhysDist::Means() const{
    return fHistogram.Means();
}

std::vector<double>
BinnedPhysDist::Variances() const{
    return fHistogram.Variances();
}

BinnedPhysDist 
BinnedPhysDist::Marginalise(const std::vector<size_t>& indices_) const{
    // Find the relative indicies indicies in 
    DataRepresentation newRep = DataRepresentation(indices_);
    std::vector<size_t> relativeIndices = newRep.GetRelativeIndices(fDataRep);

    // Marginalise the histogram
	BinnedPhysDist newPhysDist(fHistogram.Marginalise(relativeIndices));
	newPhysDist.SetDataRep(newRep);
	return newPhysDist;
}

BinnedPhysDist
BinnedPhysDist::Marginalise(size_t index_) const{
    return Marginalise(std::vector<size_t>(1, index_));
}

std::map<std::string, BinnedPhysDist> 
BinnedPhysDist::GetAllProjections() const{
  std::map<std::string, BinnedPhysDist> returnDists;
  // work out all the possible combinations of the indicies
  std::vector<std::vector<size_t> > projectionIndices = AllCombinationsShorterThanNoDuplicates<size_t>(SequentialElements(size_t(0), size_t(GetNDims())), 2);
  for(size_t i = 0; i < projectionIndices.size(); i++){
	  std::vector<size_t> indicesToKeep = projectionIndices.at(i);
	  // create a unique name based on observables
	  Formatter fm;
	  for(size_t j = 0; j < indicesToKeep.size(); j++){
		fm << GetAxes().GetAxis(j).GetName() << " ";
	  }
	  returnDists[fm] = Marginalise(indicesToKeep);
  }
  return returnDists;
}

