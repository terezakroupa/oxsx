/*****************************************/
/* A simple scale error on an observable */
/*****************************************/
#ifndef __SCALE__
#include <Systematic.h>
#include <BinnedPdf.h>

class Scale : public Systematic{
 public:
    Scale(unsigned index_, double scaleFactor_) : fScaleFactor(scaleFactor_), fAxisIndex(index_) {}
    void SetAxes(const AxisCollection&);
    const AxisCollection& GetAxes() const;

 private:
    void Construct();
    double fScaleFactor;
    unsigned fAxisIndex;
};
#endif
