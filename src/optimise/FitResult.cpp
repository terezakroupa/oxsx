#include <FitResult.h>
#include <BinnedPdf.h>
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
FitResult::SetStatSpace(BinnedPdf* statSpace_){
    fStatSpace = new BinnedPdf(*statSpace_);
}

BinnedPdf*
FitResult::GetStatSpace() const{
    return fStatSpace;
}

FitResult
FitResult::operator=(const FitResult& other_){
    if (!fStatSpace)
        fStatSpace = NULL;
    else
        fStatSpace = new BinnedPdf(*other_.fStatSpace);

    fBestFit = other_.fBestFit;
    return *this;
}

FitResult::FitResult(const FitResult& other_){
    if (!other_.fStatSpace)
        fStatSpace = NULL;

    else
        fStatSpace = new BinnedPdf(*other_.fStatSpace);
    fBestFit = other_.fBestFit;
}
