#include <AnalyticPdf.h>
#include <PdfExceptions.h>
#include <IntegrableFunction.h>
#include <DataExceptions.h>

AnalyticPdf::AnalyticPdf(IntegrableFunction* f_){
    fFunction = dynamic_cast<IntegrableFunction*>(f_->Clone());
    fNorm     = 1;
}

AnalyticPdf::~AnalyticPdf(){
    delete fFunction;
}

AnalyticPdf::AnalyticPdf(const AnalyticPdf& other_) : Pdf(other_){
    fNorm  = other_.fNorm;
    fDataRep = other_.fDataRep;
    fFunction = dynamic_cast<IntegrableFunction*>(other_.fFunction->Clone());
}

Pdf*
AnalyticPdf::Clone() const{
    return static_cast<Pdf*>(new AnalyticPdf(*this));
}

double
AnalyticPdf::operator()(const std::vector<double>& vals_) const{    
    try{
        return fFunction->operator()(vals_)/fNorm;
    }
    catch(const DimensionError&){
        throw DimensionError("AnalyticPdf passed wrong number of values!");
    }
}

double
AnalyticPdf::Probability(const EventData& event_) const{
    try{
        return operator()(event_.ToRepresentation(fDataRep));
    }

    catch(const RepresentationError& e_){
        throw RepresentationError("AnalyticPdf::Probability() failed with  "
                                  + std::string(e_.what()) + 
                                  " is the rep set correctly?");
    }
}

double 
AnalyticPdf::Integral() const{
    return fFunction->Integral();
}

void
AnalyticPdf::Normalise(){
    fNorm = Integral();
}

void
AnalyticPdf::SetDataRep(const DataRepresentation& rep_){
    fDataRep = rep_;
}

DataRepresentation
AnalyticPdf::GetDataRep() const {
    return fDataRep;
}

// Fitting this pdf to data means adjusting the underlying function
void
AnalyticPdf::MakeFittable(){
    DelegateFor(fFunction);    
}

unsigned
AnalyticPdf::GetNDims() const{
    return fFunction->GetNDims();
}
