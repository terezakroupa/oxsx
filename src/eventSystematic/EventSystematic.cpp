#include <EventSystematic.h>

void
EventSystematic::SetDataRep(const ObsSet& rep_){
    fObservables = rep_;
}

ObsSet
EventSystematic::GetDataRep() const{
    return fObservables;
}
