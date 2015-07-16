#include "NLLH.h"
#include "OneEventNLLH.h"
#include <TBranch.h>
#include <TTree.h>

double NLLH::Evaluate() const{
    return EventCalc() + Constraints() + ExtendedCorrection();
}

double NLLH::ExtendedCorrection() const{
    double rateSum = 0;
    for(size_t i = 0; i < fEventRates.size(); i++)
        rateSum += fEventRates[i];
    return rateSum;
}

double NLLH::Constraints() const{
    //FIXME
    return 0;
}

double NLLH::EventCalc() const{
    OneEventNLLH nllhcalc(&fEventTypes, fEventRates);
    double nllh = 0;
    std::vector<double>* eventData = NULL;
    TBranch *br = NULL;
    fData -> SetBranchAddress("event", &eventData, &br);
    for(unsigned i = 0; i < fNEvents; i++){
        fData->GetEntry(i);
        nllh += nllhcalc.Evaluate(eventData);
    }
    return nllh;
}

