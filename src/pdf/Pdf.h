#ifndef __PDF__
#define __PDF__
#include <vector>
#include <string>
#include <DataRepresentation.h>
#include <DataHandler.h>

class CompositePdf; 

class Pdf{
 public:
    Pdf() {}
    Pdf(const Pdf&);
    virtual ~Pdf() {}

    virtual double operator() (const std::vector<double>& vals_) const = 0;
    virtual double operator() (const DataHandler&) const;
    
    virtual double Integral() const = 0;

    virtual void   Normalise() = 0;
    virtual Pdf*   Clone() const = 0;

    CompositePdf operator* (const Pdf& other_) const;  // references are polymorphic :)
    unsigned GetNDims() const;
    
    void SetDataRep(const DataRepresentation&);
    DataRepresentation GetDataRep() const;
 protected:
    unsigned fNDims;
    DataRepresentation fDataRep;

};
#endif
