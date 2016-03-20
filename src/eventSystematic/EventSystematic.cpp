#include <EventSystematic.h>
#include <PdfExceptions.h>
#include <stdexcept>

std::vector<double>
EventSystematic::GetParameters() const {
    return fParams;
}

void
EventSystematic::SetParameters(const std::vector<double>& params_){
    fParams = params_;
}

size_t
EventSystematic::GetParamCount() const{
    return fParams.size();
}

void
EventSystematic::SetParameter(size_t index_, double val_){
    try{
        fParams[index_] = val_;
    }
    catch(const std::out_of_range& e){
        throw OutOfBoundsError("EventSystematic::SetParameter out of bounds!");
    }
}

double
EventSystematic::GetParameter(size_t index_) const {
    try{
        return fParams.at(index_);
    }
    catch(const std::out_of_range& e){
        throw OutOfBoundsError("EventSystematic::SetParameter out of bounds!");
    }
}

void
EventSystematic::SetDataRep(const DataRepresentation& rep_){
    fDataRep = rep_;
}

DataRepresentation
EventSystematic::GetDataRep() const{
    return fDataRep;
}
