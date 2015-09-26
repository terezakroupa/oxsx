#include <FitResult.h>
#include <BinnedPdf.h>

FitResult::~FitResult(){
    delete fStatSpace;
}

void
FitResult::SetBestFit(const std::vector<double>& bestFit_){
    fBestFit = bestFit_;
}

const std::vector<double>&
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
