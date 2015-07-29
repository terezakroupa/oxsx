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

    void SetPdfs(const std::vector<Event>& eventTypes_);
    void SetRates(const std::vector<double>& eventRates_);

    unsigned GetNPdfs() const {return fNEventTypes;}
    unsigned GetNSystematics() const {return 0;}

 protected:
    TTree* fData;
    unsigned fNEvents;
    std::vector<Event>  fPdfs;
    std::vector<double> fRates;
    /*std::vector<Systematics> */
    unsigned fNPdfs;
    unsigned fNSystematics;
};
#endif
