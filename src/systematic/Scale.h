/*****************************************/
/* A simple scale error on an observable */
/*****************************************/
#ifndef __SCALE__
#include <Systematic.h>
#include <BinnedPdf.h>

class Scale : public Systematic{
 public:
    Scale() : fScaleFactor(1) {}
    void SetAxes(const AxisCollection&);
    const AxisCollection& GetAxes() const;
    
    void   SetScaleFactor(double);
    double GetScaleFactor() const;
    
    void Construct();

    // Adjustable scale factor
    void MakeFittable();

 private:
    double   fScaleFactor;
};
#endif
