/*****************************************************/
/* A class to calculate the nllh for a single event  */
/*****************************************************/

#ifndef __ONE_EV_NLLH__
#define __ONE_EV_NLLH__
#include <vector>
#include "../event/Event.h"
class OneEventNLLH{
    
 public:
    OneEventNLLH(const std::vector<Event>* eventTypes_, const std::vector<double>& eventRates_);
    double Evaluate(const std::vector<double>* eventVals_) const;
    void   SetEventRates(const std::vector<double>& eventRates_);
 private:
    const std::vector<Event>*  fEventTypes;
    std::vector<double>  fEventRates;
    
};
#endif
