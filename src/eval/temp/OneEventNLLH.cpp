#include "OneEventNLLH.h"
#include <math.h>
#include <iostream>

OneEventNLLH::OneEventNLLH(const std::vector<Pdf*>& pdfs_){
    fPdfs  = pdfs_;
    fNPdfs = pdfs_.size();
}


double OneEventNLLH::Evaluate(const std::vector<double>& eventVals_) const{
    double nllh = 0;
    for (size_t i = 0; i < fRates.size(); i++){
        double prob = fPdfs.at(i) -> operator() (eventVals_);
        if (!prob)
            std::cout << "zero probability inf likelihood..." << std::endl;
        nllh -= log(fRates.at(i) * prob);
    }
    return nllh;
}


void OneEventNLLH::SetEventRates(const std::vector<double>& eventRates_){
    if (eventRates_.size() != fNPdfs)
        throw 0; // FIXME should throw dimension error
    fRates = eventRates_;
}
