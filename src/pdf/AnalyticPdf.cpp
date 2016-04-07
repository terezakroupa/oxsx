#include <AnalyticPdf.h>
#include <PdfExceptions.h>
#include <IntegrableFunction.h>

AnalyticPdf::AnalyticPdf(IntegrableFunction* f_){
    fFunction = dynamic_cast<IntegrableFunction*>(f_->Clone());
    fNorm     = 1;
}

AnalyticPdf::~AnalyticPdf(){
    delete fFunction;
}

AnalyticPdf::AnalyticPdf(const AnalyticPdf& other_){
    fNDims = other_.GetNDims();
    fNorm  = other_.fNorm;
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
AnalyticPdf::Integral() const{
    return fFunction->Integral();
}

void
AnalyticPdf::Normalise(){
    fNorm = Integral();
}


// Fitting this pdf to data means adjusting the underlying function
void
AnalyticPdf::MakeFittable(){
    DelegateFor(fFunction);    
}

