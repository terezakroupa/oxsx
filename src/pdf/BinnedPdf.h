/*********************************************/
/* This class represents an ndimensional pdf */
/*********************************************/

#ifndef __BINNED_PDF__
#define __BINNED_PDF__
#include <vector>
#include <string>
#include "AxisCollection.h"
#include "Pdf.h"

class BinnedPdf : public Pdf {
 public:
    BinnedPdf(const std::string& name_, AxisCollection axes_);

    // look at above again
    virtual double operator() (const std::vector<double>* vals_) const;
    virtual double operator() (const std::vector<double>* vals_, 
                               const std::vector<size_t>& indicies_) const;

    double GetBinContent(size_t bin_) const;
    double GetBinContent(const std::vector<size_t>& indicies_) const;
    std::string GetName() const;
    double Integral() const;

    void   Normalise();
    void   Fill(const std::vector<double>& vals_);
    void   AddBinContent(const std::vector<size_t>& indicies_, double content);
    BinnedPdf    Marginalise(const std::vector<size_t>& axisIndicies_) const; 
    BinnedPdf    Marginalise(size_t axis_) const; 
    
    std::vector<double> GetRawData() const;
 private:
    std::string fName;
    AxisCollection fAxes;
    std::vector<double> fBinContents;
};


#endif
