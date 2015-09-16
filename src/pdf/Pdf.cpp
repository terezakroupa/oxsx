#include <Pdf.h>
#include <CompositePdf.h>
#include <algorithm>

Pdf::Pdf(const Pdf& other_){
    fDataRep = other_.fDataRep;
    fNDims = other_.fNDims;
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
Pdf::Probability(const EventData& oberservations_) const{
    return operator()(oberservations_.ToRepresentation(fDataRep));
}

void
Pdf::SetDataRep(const DataRepresentation& rep_) {fDataRep = rep_;}

DataRepresentation
Pdf::GetDataRep() const {return fDataRep;}
