#include "GridSearch.h"
#include "../eval/Evaluator.h"

void GridSearch::Optimise(){
    // list of rates followed by list of systematics
    fBestRates.resize(fEvaluator->GetNEventTypes(), 0);
    fBestSystematics.resize(fEvaluator->GetNSystematics(), 0);
    fMaxVal = 0;

    // start at min value
    fCurrentRates.resize(fEvaluator->GetNEventTypes());
    fCurrentSystematics.resize(fEvaluator->GetNSystematics());

    for(size_t i = 0; i < fCurrentRates.size(); i++)
        fCurrentRates[i] = fRateSteps[i].min;

    for(size_t i = 0; i < fCurrentSystematics.size(); i++)
        fCurrentRates[i] = fSystematicSteps[i].min;

    // Step through and record the max value
    while(IncrementSystematic(0)){
        // Recalculate the systematics here
        
        while(IncrementRate(0)){
            // calculate the new value
            // if bigger, grab this as new best fit
            fEvaluator->SetEventRates(fCurrentRates);
            double currentVal = fEvaluator->Evaluate();
            if (currentVal > fMaxVal){
                fMaxVal = currentVal;
                fBestRates = fCurrentRates;
                fBestSystematics = fCurrentSystematics;
            }

        } // rate  loop
    }// systematic loop
}

bool GridSearch::IncrementSystematic(size_t index_){
    if (!fCurrentSystematics.size())
        return false;

    fCurrentSystematics[index_] += fSystematicSteps[index_].step;

    // wrap around past the maximum
    if (fCurrentSystematics[index_] > fSystematicSteps[index_].max){
        fCurrentSystematics[index_] = fSystematicSteps[index_].min;
        
        // if on the last index no rippling to do 
        if (index_ == fSystematicSteps.size() - 1)
            return false;

        // ripple up to next index 
        if (IncrementSystematic(index_ + 1)) // propagate the false down
            return true;
        else
            return false;
    }
    return true;
}

bool GridSearch::IncrementRate(size_t index_){
    fCurrentRates[index_] += fRateSteps[index_].step;

    // wrap around past the maximum
    if (fCurrentRates[index_] > fRateSteps[index_].max){
        fCurrentRates[index_] = fRateSteps[index_].min;

        // if its the last index no rippling to do
        if (index_ == fRateSteps.size() - 1)
            return false;

        // ripple up to next index
        if (IncrementRate(index_ + 1)) // propagate the false down
            return true;
        else
            return false;

    }
    return true;
}
