#ifndef __PDF__
#define __PDF__
#include <vector>

class CompositePdf; 

class Pdf{
 public:
    Pdf() {}

    virtual double operator() (const std::vector<double>& vals_) const = 0;
    virtual ~Pdf() {}
    virtual double Integral() const = 0;
    virtual void   Normalise() = 0;
    virtual Pdf*   Clone() const = 0;

    CompositePdf operator* (const Pdf& other_) const;  // references are polymorphic :)
    unsigned GetNDims() const;

 private:
    unsigned fNDims;
};
#endif
