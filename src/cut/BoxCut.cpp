#include <BoxCut.h>
#include <PdfExceptions.h>
bool
BoxCut::PassesCut(const EventData& ev_) const{
    double val = 0;
    try{
        val = ev_.GetDatum(fDim);
    }
    catch(const DimensionError&){
        throw DimensionError("Cut::Cut to non-existent data observable requested!");
    }
    
    return (val < fUpperLim && val > fLowerLim);
}


Cut*
BoxCut::Clone() const{
  return new BoxCut(*this);
}
