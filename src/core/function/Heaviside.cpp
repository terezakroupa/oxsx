#include <Heaviside.h>
#include <PdfExceptions.h>
#include <SystematicExceptions.h>
#include <iostream>

Heaviside::Heaviside(unsigned nDims_){
    SetNDims(nDims_);
    fStepPosition.resize(nDims_, 0);
    fSidedness.resize(nDims_, IGNORE);
}

void
Heaviside::AddConstraint(unsigned dim_, double pos_, Sidedness side_){
    if (dim_ >= GetNDims())
        throw DimensionError("Heaviside:: Tried to add constraint on non-existent dim!");
    if (side_ != MAXIMUM && side_!= MINIMUM)
        throw ParameterError("Heaviside:: Tried to add ambiguous constraint - MAXUMUM or MINIMUM");
    
    fStepPosition[dim_] = pos_;
    fSidedness[dim_]    = side_; 
}

double
Heaviside::operator()(const std::vector<double>& vals_) const{
    if (vals_.size() != GetNDims())
        throw DimensionError("Heaviside:: Passed wrong number of arguments in");
    // loop over all the dimensions, return 0 if out of bounds otherwise return 1
    for(size_t i = 0; i < GetNDims(); i++){
        if (fSidedness.at(i) == IGNORE)
            continue;
        
        double distToStep = vals_.at(i) - fStepPosition.at(i);
        if(fSidedness.at(i) == MINIMUM)
            distToStep *= -1;

        if (distToStep > 0)
            return 0;
    }
    
    return 1;
}
