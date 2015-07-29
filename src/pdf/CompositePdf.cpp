#include "CompositePdf.h"
#include <iostream>
CompositePdf::CompositePdf(const Pdf* p1_, const Pdf* p2_) {
    fPdfPtrs.push_back(p1_ -> Clone());
    fPdfPtrs.push_back(p2_ -> Clone());
    fNDims = p1_ -> GetNDims() + p2_ -> GetNDims();

}

CompositePdf::CompositePdf(const std::vector<Pdf*>& pdfs_){
    // if one of the pdfs is composite itself the copy will happen recursively all the way down
    fNDims = 0;
    for(size_t i = 0; i < pdfs_.size(); i++){
        fPdfPtrs.push_back(pdfs_[i] -> Clone());
        fNDims += pdfs_[i] -> GetNDims();
    }
}

CompositePdf::~CompositePdf() {
    for(size_t i = 0; i < fPdfPtrs.size(); i++)
        delete fPdfPtrs[i];
}

double CompositePdf::operator() (const std::vector<double>& vals_) const{
    double prob = 1;
    for(size_t i = 0; i < fPdfPtrs.size(); i++)
        prob *= fPdfPtrs[i] -> operator() (vals_);
    return prob;
}

void CompositePdf::Normalise(){
    for(size_t i = 0; i < fPdfPtrs.size(); i++)
        fPdfPtrs[i] -> Normalise();
}

double CompositePdf::Integral() const{
    double integral = 1;
    for(size_t i = 0; i < fPdfPtrs.size(); i++)
        integral *= fPdfPtrs[i] -> Integral();
    return integral;
}

Pdf* CompositePdf::Clone() const {
    Pdf *cp = new CompositePdf(fPdfPtrs);
    return static_cast<Pdf*>(cp);
}
