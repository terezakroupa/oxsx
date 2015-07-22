/***************************************************************************************/
/* A class to represent a systematic measurement error. Maps one binned pdf to another */
/***************************************************************************************/
// Do you want a treatement for analytics? Probably not
// Need to check probability conservation - in constructor?
#ifndef __SYSTEMATIC__
#define __SYSTEMATIC__
#include "../pdf/binned/AxisCollection.h"
class BinnedPdf;

class Systematic{
 public:
    Systematic(const AxisCollection& axes_);
    virtual BinnedPdf operator() (const BinnedPdf& pdf_, 
                                  const std::vector<size_t>& indicies_) const;

 protected:
    AxisCollection fAxes;
    std::vector<std::vector<double> > fResponse;
    unsigned fNBins;
    unsigned fNDims;
};
#endif
