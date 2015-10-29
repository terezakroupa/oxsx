#include <Minuit.h>
#include <Minuit2/MnMigrad.h>
#include <Minuit2/MnMinimize.h>
#include <Minuit2/MnSimplex.h>
#include <Minuit2/FunctionMinimum.h>
#include <Minuit2/MnUserParameters.h>
#include <FitResult.h>

using ROOT::Minuit2::MnMigrad;
using ROOT::Minuit2::MnMinimize;
using ROOT::Minuit2::MnSimplex;
using ROOT::Minuit2::MnUserParameters;

// FIXME:: CHeck the length of the vectors as you set them match fNparams

Minuit::~Minuit(){
    delete fMinimiser;
}

void
Minuit::SetMethod(const std::string& method_){
    fMethod = method_;   
}

std::string
Minuit::GetMethod() const{
    return fMethod;
}

void
Minuit::SetInitialErrors(const std::vector<double>& errs_){
    fInitialErrors = errs_;
}

void
Minuit::SetInitialValues(const std::vector<double>& vals_){
    fInitialValues = vals_;
}

void
Minuit::SetUpperContourEdge(double val_){
    fMinuitFCN.SetUp(val_);
}

double
Minuit::GetUpperContourEdge() const{
    return fMinuitFCN.GetUp();
}

void
Minuit::SetMaxima(const std::vector<double>& maxima_) {fMaxima = maxima_;}

std::vector<double> 
Minuit::GetMaxima() const {return fMaxima;}

void
Minuit::SetMinima(const std::vector<double>& minima_) {fMinima = minima_;}

std::vector<double> 
Minuit::GetMinima() const {return fMinima;}

void 
Minuit::Initialise(){
    delete fMinimiser;
    fMinimiser = NULL;

    // max or min?
    if(fMaximising)
        fMinuitFCN.SetSignFlip(true);

    // Create parameters and set limits
    MnUserParameters params(fInitialValues, fInitialErrors);
    if(fMinima.size() && fMaxima.size())
        for(size_t i = 0; i < fInitialValues.size(); i++)
            params.SetLimits(i, fMinima.at(i), fMaxima.at(i));
        
    if("Migrad" == fMethod)
        fMinimiser = new MnMigrad(fMinuitFCN, params);

    else if ("Minimize" == fMethod)
        fMinimiser = new MnMinimize(fMinuitFCN, params);
    
    else if ("Simplex" == fMethod)
        fMinimiser = new MnSimplex(fMinuitFCN, params);
}

void
Minuit::Fix(size_t index_){
    fMinimiser->Fix(index_);
}

void
Minuit::Release(size_t index_){
    fMinimiser->Release(index_);
}

void
Minuit::SetMaxCalls(unsigned max_) {fMaxCalls = max_;}

unsigned
Minuit::GetMaxCalls() const {return fMaxCalls;}

void 
Minuit::RemoveLimits(size_t index_){
    fMinimiser->RemoveLimits(index_);
}

const FitResult&
Minuit::Optimise(){
    if(!fMinimiser)
        Initialise();

    // defaults are same as ROOT defaults
    ROOT::Minuit2::FunctionMinimum fnMin  = fMinimiser -> operator()(fMaxCalls, fTolerance); 

    fFitResult.SetBestFit(fMinimiser -> Params());
    fFitResult.SetValid(fnMin.IsValid());
    return fFitResult;
}



void 
Minuit::SetTolerance(double tol_) {fTolerance = tol_;}

double
Minuit::GetTolerance() const {return fTolerance;}

FitResult
Minuit::GetFitResult() const{
    return fFitResult;
    
}
