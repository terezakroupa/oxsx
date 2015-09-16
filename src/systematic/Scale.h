/*****************************************/
/* A simple scale error on an observable */
/*****************************************/
#ifndef __SCALE__
#include <Systematic.h>
#include <BinnedPdf.h>

class Scale : public Systematic{
 public:
    Scale(unsigned axisIndex_);
    void SetAxes(const AxisCollection&);
    const AxisCollection& GetAxes() const;
    
    void SetScaleFactor(double);
    double GetScaleFactor() const;

 private:
    void Construct();
    unsigned fAxisIndex;
};
#endif
