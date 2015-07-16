#include "Evaluator.h"
#include <TTree.h>

Evaluator::Evaluator(TTree* data_){
    fData = data_;
    fNEvents = data_->GetEntries();
}


void Evaluator::SetEventTypes(const std::vector<Event>& eventTypes_){
    fEventTypes = eventTypes_;
    fNEventTypes = eventTypes_.size();
}
void Evaluator::SetEventRates(const std::vector<double>& eventRates_){
    fEventRates = eventRates_;
}

void Evaluator::AddEventType(const Event& event_, double rate_){
    fEventTypes.push_back(event_);
    fEventRates.push_back(rate_);
}
