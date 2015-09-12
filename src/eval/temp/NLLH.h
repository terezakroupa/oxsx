/***************************************************************************/
/* A class to loop over the events in a root ntuple and calculate the NLLH */
/***************************************************************************/

#ifndef __NLLH__
#define __NLLH__
#include <vector>
#include "../event/Event.h"
#include "Evaluator.h"

class NLLH : public Evaluator{
 public:
    NLLH(TTree* data_) : Evaluator(data_) {}
    virtual double Evaluate() const;
    
 private:
    double ExtendedCorrection() const;
    double Constraints() const;
    double EventCalc() const;

};
#endif
