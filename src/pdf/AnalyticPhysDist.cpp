#include <AnalyticPhysDist.h>
#include <Exceptions.h>
#include <PhysDist.h>
#include <PDF.h>

AnalyticPhysDist::AnalyticPhysDist(PDF* f_){
    fFunction = dynamic_cast<PDF*>(f_->Clone());
    fNorm     = 1;
}

AnalyticPhysDist::~AnalyticPhysDist(){
    delete fFunction;
}

AnalyticPhysDist::AnalyticPhysDist(const AnalyticPhysDist& other_){
    fNorm  = other_.fNorm;
    fDataRep = other_.fDataRep;
    fFunction = dynamic_cast<PDF*>(other_.fFunction->Clone());
}

PhysDist*
AnalyticPhysDist::Clone() const{
    return static_cast<PhysDist*>(new AnalyticPhysDist(*this));
}

double
AnalyticPhysDist::operator()(const std::vector<double>& vals_) const{    
    try{
        return fFunction->operator()(vals_)/fNorm;
    }
    catch(const DimensionError& e_){
        throw DimensionError(std::string("AnalyticPhysDist internal function ::") + e_.what());
                             
                             
    }
}

double
AnalyticPhysDist::Probability(const EventData& event_) const{
    try{
        return operator()(event_.ToRepresentation(fDataRep));
    }

    catch(const RepresentationError& e_){
        throw RepresentationError("AnalyticPhysDist::Probability() failed with  "
                                  + std::string(e_.what()) + 
                                  " is the rep set correctly?");
    }
}

double 
AnalyticPhysDist::Integral() const{
    return fFunction->Integral();
}

void
AnalyticPhysDist::Normalise(){
    fNorm = Integral();
}

void
AnalyticPhysDist::SetDataRep(const DataRepresentation& rep_){
    fDataRep = rep_;
}

DataRepresentation
AnalyticPhysDist::GetDataRep() const {
    return fDataRep;
}

unsigned
AnalyticPhysDist::GetNDims() const{
    return fFunction->GetNDims();
}

// Fitting this pdf to data means adjusting the underlying function
void
AnalyticPhysDist::MakeFittable(){
    fFunction -> MakeFittable();
}

std::vector<std::string> 
AnalyticPhysDist::GetParameterNames() const{
    std::vector<std::string> funcNames = fFunction->GetParameterNames();
    for(size_t i = 0; i < funcNames.size(); i++)
        funcNames[i] = "Analytic Dist: " + funcNames[i];
    return funcNames;
}

std::vector<double>
AnalyticPhysDist::GetParameters() const{
    return fFunction->GetParameters();
}

size_t 
AnalyticPhysDist::GetParameterCount() const{
    return fFunction->GetParameterCount();
}

void
AnalyticPhysDist::SetParameters(const std::vector<double>& params_){
    try{
        fFunction->SetParameters(params_);
    }
    catch(const ParameterCountError& e_){
        throw ParameterCountError(std::string("AnalyticPhysDist internal function : ") + e_.what());

    }
}
