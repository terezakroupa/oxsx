#include <EventSystematic.h>

void
EventSystematic::SetDataRep(const DataRepresentation& rep_){
    fDataRep = rep_;
}

DataRepresentation
EventSystematic::GetDataRep() const{
    return fDataRep;
}
