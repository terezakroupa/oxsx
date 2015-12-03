#include <BoolCut.h>
#include <PdfExceptions.h>
#include <EventData.h>

bool
BoolCut::PassesCut(const EventData& ev_) const{
  double val = 0;
  try{
    val = ev_.GetDatum(fDim);
  }
  catch(const DimensionError&){
    throw DimensionError("Cut::Cut to non-existent data observable requested!");
  }

  return val == fVal;
}


BoolCut::BoolCut(const BoolCut& other_){
  fVal = other_.fVal;
  fDim = other_.fDim;  
}

Cut*
BoolCut::Clone() const{
  return new BoolCut(*this);
}
