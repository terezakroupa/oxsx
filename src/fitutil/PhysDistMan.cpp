#include <PhysDistMan.h>
#include <PhysDist.h>
#include <EventData.h>
#include <Exceptions.h>

PhysDistMan::~PhysDistMan(){
    for(size_t i = 0; i < fDists.size(); i++)
        delete fDists[i];
}

void 
PhysDistMan::AddPhysDist(PhysDist * pdf_){
    if (!fDists.size())
        fNDims = pdf_->GetNDims();

    else if(pdf_->GetNDims() != fNDims)
        throw DimensionError("PhysDistMan::AddPhysDist", fNDims, pdf_->GetNDims(),
                             " dimensions in added pdf");

    fDists.push_back(pdf_->Clone());    
    fNDists++;
    fNormalisations.resize(fNDists, 0);
}

void
PhysDistMan::AddPhysDists(const std::vector<PhysDist*>& pdfs_){
    for(size_t i = 0; i < pdfs_.size(); i++)
        AddPhysDist(pdfs_.at(i));
}

double
PhysDistMan::Probability(const EventData& event_) const{
    double prob = 0;
    for(size_t i = 0; i < fDists.size(); i++)
        prob += fNormalisations.at(i) * fDists.at(i)->Probability(event_);
    
    return prob;
}

const std::vector<double>&
PhysDistMan::GetNormalisations() const{
    return fNormalisations;
}

void
PhysDistMan::SetNormalisations(const std::vector<double>& norms_){
    if (norms_.size() != fNDists)
        throw DimensionError("PhysDistMan::SetNormalisations", fNDists, 
                             norms_.size());
    fNormalisations = norms_;
}

size_t 
PhysDistMan::GetNDims() const{
    return fNDims;
}

size_t 
PhysDistMan::GetNDists() const{
    return fNDists;
}

// Make a fittable component - i.e. rescale pdfs inside to fit
void
PhysDistMan::MakeFittable(){
    fParameterManager.Clear();
    fNormalisations.resize(fNDists);
    fParameterManager.AddContainer<std::vector<double> >(fNormalisations, 
                                                         "Dist Normalisation");
}

std::vector<std::string>
PhysDistMan::GetParameterNames() const{
    return fParameterManager.GetParameterNames();
}
std::vector<double>
PhysDistMan::GetParameters() const{
    return fParameterManager.GetParameters();
}

size_t 
PhysDistMan::GetParameterCount() const{
    return fParameterManager.GetParameterCount();
}

void
PhysDistMan::SetParameters(const std::vector<double>& params_){
    try{
        fParameterManager.SetParameters(params_);
    }
    catch(const ParameterCountError& e_){
        throw ParameterCountError(std::string("PhysDistMan:: ") + e_.what());
    }
}
