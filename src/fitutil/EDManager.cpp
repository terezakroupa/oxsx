#include <EDManager.h>
#include <EventDistribution.h>
#include <Event.h>
#include <Exceptions.h>

EDManager::~EDManager(){
    for(size_t i = 0; i < fDists.size(); i++)
        delete fDists[i];
}

void 
EDManager::AddEventDistribution(EventDistribution * pdf_){
    if (!fDists.size())
        fNDims = pdf_->GetNDims();

    else if(pdf_->GetNDims() != fNDims)
        throw DimensionError("EDManager::AddEventDistribution", fNDims, pdf_->GetNDims(),
                             " dimensions in added pdf");

    fDists.push_back(pdf_->Clone());    
    fNDists++;
    fNormalisations.resize(fNDists, 0);
}

void
EDManager::AddEventDistributions(const std::vector<EventDistribution*>& pdfs_){
    for(size_t i = 0; i < pdfs_.size(); i++)
        AddEventDistribution(pdfs_.at(i));
}

double
EDManager::Probability(const Event& event_) const{
    double prob = 0;
    for(size_t i = 0; i < fDists.size(); i++)
        prob += fNormalisations.at(i) * fDists.at(i)->Probability(event_);
    
    return prob;
}

const std::vector<double>&
EDManager::GetNormalisations() const{
    return fNormalisations;
}

void
EDManager::SetNormalisations(const std::vector<double>& norms_){
    if (norms_.size() != fNDists)
        throw DimensionError("EDManager::SetNormalisations", fNDists, 
                             norms_.size());
    fNormalisations = norms_;
}

size_t 
EDManager::GetNDims() const{
    return fNDims;
}

size_t 
EDManager::GetNDists() const{
    return fNDists;
}

// Make a fittable component - i.e. rescale pdfs inside to fit
void
EDManager::MakeFittable(){
    fParameterManager.Clear();
    fNormalisations.resize(fNDists);
    fParameterManager.AddContainer<std::vector<double> >(fNormalisations, 
                                                         "Dist Normalisation");
}

std::vector<std::string>
EDManager::GetParameterNames() const{
    return fParameterManager.GetParameterNames();
}
std::vector<double>
EDManager::GetParameters() const{
    return fParameterManager.GetParameters();
}

size_t 
EDManager::GetParameterCount() const{
    return fParameterManager.GetParameterCount();
}

void
EDManager::SetParameters(const std::vector<double>& params_){
    try{
        fParameterManager.SetParameters(params_);
    }
    catch(const ParameterCountError& e_){
        throw ParameterCountError(std::string("EDManager:: ") + e_.what());
    }
}
