#include <Pdf.h>
#include <CompositePdf.h>
#include <algorithm>

Pdf::Pdf(const Pdf& other_){
    fDataRep = other_.fDataRep;
    fNDims = fNDims;
}

CompositePdf 
Pdf::operator* (const Pdf& other_) const {
    return CompositePdf(this, &other_);
}

unsigned Pdf::GetNDims() const{
    return fNDims;
}

//FIXME::add try catch
double 
Pdf::operator() (const DataHandler& oberservations_) const{
    return operator()(oberservations_.ToRepresentation(fDataRep));
}
