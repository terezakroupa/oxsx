#include <Function.h>

void
Function::SetNDims(unsigned nDims_){
    fNDims = nDims_;    
}

unsigned 
Function::GetNDims() const{
    return fNDims;
}

