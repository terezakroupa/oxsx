#ifndef __OXSX_CUT__
#define __OXSX_CUT__
#include <EventData.h>
#include <limits>

class Cut{
 public:
    Cut(size_t dim_) : fDim(dim_), fUpperLim(std::numeric_limits<double>::infinity()), 
                       fLowerLim(-1 * std::numeric_limits<double>::infinity()) {}
    ~Cut(){}

    bool PassesCut(const EventData& ev_) const;
    
    void    SetLowerLimit(double lower_) {fLowerLim = lower_;} 
    double  GetLowerLimit() const {return fLowerLim;}

    void    SetUpperLimit(double upper_) {fUpperLim = upper_;} 
    double  GetUpperLimit() const {return fUpperLim;}

 private:
    size_t fDim;
    double fUpperLim;
    double fLowerLim;
    
};
#endif
