#include <BinnedED.h>
#include <Exceptions.h>
#include <Combinations.hpp>

BinnedED::BinnedED(const AxisCollection& axes_){
    fHistogram.SetAxes(axes_);
}

BinnedED::BinnedED(const Histogram& histo_){
    fHistogram = histo_;
}

void
BinnedED::SetDataRep(const DataRepresentation& rep_){
    fDataRep = rep_;
}

DataRepresentation
BinnedED::GetDataRep() const {
    return fDataRep;
}

const Histogram&
BinnedED::GetHistogram() const{
    return fHistogram;
}

void
BinnedED::SetHistogram(const Histogram& hist_){
    fHistogram = hist_;
}

void 
BinnedED::Fill(const EventData& data_, double weight_){
    try{
        fHistogram.Fill(data_.ToRepresentation(fDataRep), weight_);
    }
    catch (const DimensionError& e_){
        throw RepresentationError(std::string("Representation in compatible with pdf ") + e_.what());
    }
}

size_t 
BinnedED::FindBin(const EventData& data_) const{
    try{
        return fHistogram.FindBin(data_.ToRepresentation(fDataRep));    
    }
    catch (const DimensionError& e_){
        throw RepresentationError(std::string("Representation in compatible with pdf ") + e_.what());
    }    
}

EventDistribution* 
BinnedED::Clone() const{
    return static_cast<EventDistribution*>(new BinnedED(*this));
}


//////////////////////////////////////////////////////////////////////////////////////////
// All methods below this line just forward the call to the underlying histogram object //
//////////////////////////////////////////////////////////////////////////////////////////

void 
BinnedED::SetAxes(const AxisCollection& axes_){
    fHistogram.SetAxes(axes_);

}

const AxisCollection& 
BinnedED::GetAxes() const{
    return fHistogram.GetAxes();
}

double 
BinnedED::Probability(const std::vector<double>& vals_) const{
    return fHistogram.GetBinContent(fHistogram.FindBin(vals_))/fHistogram.Integral();
}

double
BinnedED::Probability(const EventData& oberservations_) const{
    try{
        return Probability(oberservations_.ToRepresentation(fDataRep));
    }

    catch(const RepresentationError& e_){
        throw RepresentationError("BinnedED::Probability() failed with  " 
                                  + std::string(e_.what()) 
                                  + " is the rep set correctly?");
    }
}

double 
BinnedED::Integral() const{
    return fHistogram.Integral();
}

void 
BinnedED::Normalise(){
    fHistogram.Normalise();
}

void
BinnedED::Scale(double s_){
    fHistogram.Scale(s_);
}

void 
BinnedED::Fill(const std::vector<double>& vals_, double weight_){
    fHistogram.Fill(vals_, weight_);
}


void 
BinnedED::Fill(double vals_, double weight_){
    fHistogram.Fill(vals_, weight_);
}

size_t 
BinnedED::FindBin(const std::vector<double>& vals_) const{
    return fHistogram.FindBin(vals_);
    
}

double 
BinnedED::GetBinContent(size_t bin_) const{
    return fHistogram.GetBinContent(bin_);
}

void 
BinnedED::AddBinContent(size_t bin_, double content_){
    fHistogram.AddBinContent(bin_, content_);
}

void 
BinnedED::SetBinContent(size_t bin_, double content_){
    fHistogram.SetBinContent(bin_, content_);
}

size_t 
BinnedED::GetNBins() const{
    return fHistogram.GetNBins();
}

unsigned
BinnedED::GetNDims() const{
    return fHistogram.GetNDims();
}

void 
BinnedED::Empty(){
    fHistogram.Empty();
}

size_t 
BinnedED::FlattenIndices(const std::vector<size_t>& indices_) const{
    return fHistogram.FlattenIndices(indices_);
}

std::vector<size_t> 
BinnedED::UnpackIndices(size_t bin_) const{
    return fHistogram.UnpackIndices(bin_);
}

std::vector<double> 
BinnedED::GetBinContents() const{
    return fHistogram.GetBinContents();
}
void 
BinnedED::SetBinContents(const std::vector<double>& data_){
    return fHistogram.SetBinContents(data_);
}

std::vector<double>
BinnedED::Means() const{
    return fHistogram.Means();
}

std::vector<double>
BinnedED::Variances() const{
    return fHistogram.Variances();
}

BinnedED 
BinnedED::Marginalise(const std::vector<size_t>& indices_) const{
    // Find the relative indicies indicies in 
    DataRepresentation newRep = DataRepresentation(indices_);
    std::vector<size_t> relativeIndices = newRep.GetRelativeIndices(fDataRep);

    // Marginalise the histogram
	BinnedED newPhysDist(fHistogram.Marginalise(relativeIndices));
	newPhysDist.SetDataRep(newRep);
	return newPhysDist;
}

BinnedED
BinnedED::Marginalise(size_t index_) const{
    return Marginalise(std::vector<size_t>(1, index_));
}

std::map<std::string, BinnedED> 
BinnedED::GetAllProjections() const{
  std::map<std::string, BinnedED> returnDists;
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

