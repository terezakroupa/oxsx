/*
A one sided cut. 
*/
#ifndef __OXSX_LINECUT__
#define __OXSX_LINECUT__
#include <Cut.h>
#include <string>

class LineCut : public Cut{
 public:
    LineCut(const std::string& obs_, double val_, 
            const std::string& side_);

    virtual ~LineCut(){}
    virtual Cut* Clone() const;

    virtual bool PassesCut(const Event& ev_) const;
    
    void   SetCutValue(double);
    double GetCutValue() const;

    void SetSidedness(const std::string&); // "upper" or "lower" (bounds)
    std::string GetSidedness() const;

 private:
    std::string fObs;
    double fVal;
    std::string fSidedness;
};
#endif
