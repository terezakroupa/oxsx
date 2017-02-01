/*****************************************/
/* A simple scale error on an observable */
/*****************************************/
#ifndef __OXSX_SCALE__
#include <Systematic.h>

class Scale : public Systematic{
 public:
    Scale() : fScaleFactor(1) {}
    void   SetScaleFactor(double);
    double GetScaleFactor() const;
    
    void Construct();

    // Adjustable scale factor
    void   MakeFittable() {}
    std::vector<std::string> GetParameterNames() const;
    void   SetParameterNames(const std::vector<std::string>&);

    std::vector<double>      GetParameters() const;
    size_t GetParameterCount() const;
    void   SetParameters(const std::vector<double>&);

    double GetParameter(const std::string&) const;
    void   SetParameter(const std::string&, double);
    
 private:
    double   fScaleFactor;
    std::string fScaleName;
};
#endif
