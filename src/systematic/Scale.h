/*****************************************/
/* A simple scale error on an observable */
/*****************************************/
#ifndef __OXSX_SCALE__
#include <Systematic.h>

class Scale : public Systematic{
 public:
    Scale() : fScaleFactor(1) {}
    void  SetAxes(const AxisCollection&);
    const AxisCollection& GetAxes() const;
    
    void   SetScaleFactor(double);
    double GetScaleFactor() const;
    
    void Construct();

    // Adjustable scale factor
    void   MakeFittable() {}
    std::vector<std::string> GetParameterNames() const;
    std::vector<double>      GetParameters() const;
    size_t GetParameterCount() const;
    void   SetParameters(const std::vector<double>&);
 
 private:
    double   fScaleFactor;
};
#endif
