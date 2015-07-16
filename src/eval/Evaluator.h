/****************************************/
/* Abstract base class for an evaluator */
/****************************************/
#ifndef __EVALUATOR__
#define __EVALUATOR__
#include <vector>
#include "../event/Event.h"
class TTree;


class Evaluator{
 public:
    Evaluator (TTree* data_);
    virtual ~Evaluator() {};
    virtual double Evaluate() const = 0;

    void SetEventTypes(const std::vector<Event>& eventTypes_);
    void SetEventRates(const std::vector<double>& eventRates_);

    void AddEventType(const Event& event_, double rate_);

    unsigned GetNEventTypes() const {return fNEventTypes;}
    unsigned GetNSystematics() const {return 0;}

 protected:
    TTree* fData;
    unsigned fNEvents;
    unsigned fNEventTypes;
    unsigned fNSystematics;
    std::vector<Event> fEventTypes;
    /*std::vector<Systematics> */
    std::vector<double> fEventRates;
};
#endif
