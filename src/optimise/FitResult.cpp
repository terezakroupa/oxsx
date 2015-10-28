#include <FitResult.h>
#include <Histogram.h>
#include <iostream>
FitResult::~FitResult(){
    delete fStatSpace;
}

void
FitResult::SetBestFit(const std::vector<double>& bestFit_){
    fBestFit = bestFit_;
}

std::vector<double>
FitResult::GetBestFit() const{
    return fBestFit;
}

void
FitResult::SetStatSpace(const Histogram& statSpace_){
    fStatSpace = new Histogram(statSpace_);
}

const Histogram&
FitResult::GetStatSpace() const{
    return *fStatSpace;
}

FitResult
FitResult::operator=(const FitResult& other_){
    if (!fStatSpace)
        fStatSpace = NULL;
    else
        fStatSpace = new Histogram(*other_.fStatSpace);
    fIsValid = other_.fIsValid;
    fBestFit = other_.fBestFit;
    fStatSample = other_.fStatSample;
    return *this;
}

FitResult::FitResult(const FitResult& other_){
    if (!other_.fStatSpace)
        fStatSpace = NULL;

    else
        fStatSpace = new Histogram(*other_.fStatSpace);
    fStatSample = other_.fStatSample;
    fBestFit = other_.fBestFit;
    fIsValid = other_.fIsValid;
}

const std::vector<std::vector<double> >&
FitResult::GetStatSample() const{
    return fStatSample;
}

void
FitResult::SetStatSample(const std::vector<std::vector<double> >& statSample_){
    fStatSample = statSample_;
}

bool
FitResult::GetValid() const {
    return fIsValid;
}

void
FitResult::SetValid(bool b_){
    fIsValid = b_;
}
