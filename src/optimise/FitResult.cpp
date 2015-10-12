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
FitResult::SetStatSpace(Histogram* statSpace_){
    fStatSpace = new Histogram(*statSpace_);
}

Histogram*
FitResult::GetStatSpace() const{
    return fStatSpace;
}

FitResult
FitResult::operator=(const FitResult& other_){
    if (!fStatSpace)
        fStatSpace = NULL;
    else
        fStatSpace = new Histogram(*other_.fStatSpace);

    fBestFit = other_.fBestFit;
    return *this;
}

FitResult::FitResult(const FitResult& other_){
    if (!other_.fStatSpace)
        fStatSpace = NULL;

    else
        fStatSpace = new Histogram(*other_.fStatSpace);
    fBestFit = other_.fBestFit;
}

std::vector<std::vector<double> > 
FitResult::GetStatSample() const{
    return fStatSample;
}

void
FitResult::SetStatSample(const std::vector<std::vector<double> >& statSample_){
    fStatSample = statSample_;
}
