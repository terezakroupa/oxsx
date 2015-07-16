#include "OneEventNLLH.h"
#include <math.h>
#include <iostream>

double OneEventNLLH::Evaluate(const std::vector<double>* eventVals_) const{
    double nllh = 0;
    for (size_t i = 0; i < fEventRates.size(); i++){
        double prob = fEventTypes->at(i).Probability(eventVals_);
        if (!prob)
            std::cout << "zero probability inf likelihood..." << std::endl;
        nllh -= log(fEventRates.at(i) * prob);
    }
    
    return nllh;
}

OneEventNLLH::OneEventNLLH(const std::vector<Event>* eventTypes_, 
                           const std::vector<double>& eventRates_){
    fEventTypes = eventTypes_;
    fEventRates = eventRates_;
}

