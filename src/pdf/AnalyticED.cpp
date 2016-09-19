#include <AnalyticED.h>
#include <Exceptions.h>
#include <EventDistribution.h>
#include <PDF.h>

AnalyticED::AnalyticED(PDF* f_){
    fFunction = dynamic_cast<PDF*>(f_->Clone());
    fNorm     = 1;
}

AnalyticED::~AnalyticED(){
    delete fFunction;
}

AnalyticED::AnalyticED(const AnalyticED& other_){
    fNorm  = other_.fNorm;
    fDataRep = other_.fDataRep;
    fFunction = dynamic_cast<PDF*>(other_.fFunction->Clone());
}

EventDistribution*
AnalyticED::Clone() const{
    return static_cast<EventDistribution*>(new AnalyticED(*this));
}

double
AnalyticED::Probability(const std::vector<double>& vals_) const{    
    try{
        return fFunction->operator()(vals_)/fNorm;
    }
    catch(const DimensionError& e_){
        throw DimensionError(std::string("AnalyticED internal function ::") + e_.what());
                             
                             
    }
}

double
AnalyticED::Probability(const EventData& event_) const{
    try{
        return Probability(event_.ToRepresentation(fDataRep));
    }

    catch(const RepresentationError& e_){
        throw RepresentationError("AnalyticED::Probability() failed with  "
                                  + std::string(e_.what()) + 
                                  " is the rep set correctly?");
    }
}

double 
AnalyticED::Integral() const{
    return fNorm;
}

void
AnalyticED::Normalise(){
    fNorm = 1;
}

void
AnalyticED::SetDataRep(const DataRepresentation& rep_){
    fDataRep = rep_;
}

DataRepresentation
AnalyticED::GetDataRep() const {
    return fDataRep;
}

unsigned
AnalyticED::GetNDims() const{
    return fFunction->GetNDims();
}

// Fitting this pdf to data means adjusting the underlying function
void
AnalyticED::MakeFittable(){
    fFunction -> MakeFittable();
}

std::vector<std::string> 
AnalyticED::GetParameterNames() const{
    std::vector<std::string> funcNames = fFunction->GetParameterNames();
    for(size_t i = 0; i < funcNames.size(); i++)
        funcNames[i] = "Analytic Dist: " + funcNames[i];
    return funcNames;
}

std::vector<double>
AnalyticED::GetParameters() const{
    return fFunction->GetParameters();
}

size_t 
AnalyticED::GetParameterCount() const{
    return fFunction->GetParameterCount();
}

void
AnalyticED::SetParameters(const std::vector<double>& params_){
    try{
        fFunction->SetParameters(params_);
    }
    catch(const ParameterCountError& e_){
        throw ParameterCountError(std::string("AnalyticED internal function : ") + e_.what());

    }
}
