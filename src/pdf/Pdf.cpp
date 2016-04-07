#include <Pdf.h>
#include <CompositePdf.h>
#include <algorithm>
#include <iostream>
#include <PdfExceptions.h>
#include <DataExceptions.h>


Pdf::Pdf(const Pdf& other_){
    fDataRep = other_.fDataRep;    
}
unsigned Pdf::GetNDims() const{
    return fNDims;
}


double 
Pdf::Probability(const EventData& oberservations_) const{
    try{
        return operator()(oberservations_.ToRepresentation(fDataRep));
    }

    catch(const RepresentationError& e_){
        throw RepresentationError("Pdf::Probability() failed with  " + std::string(e_.what()) + " is the rep set correctly?");

    }
}

void
Pdf::SetDataRep(const DataRepresentation& rep_) {fDataRep = rep_;}

DataRepresentation
Pdf::GetDataRep() const {return fDataRep;}
