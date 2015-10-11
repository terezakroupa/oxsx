/*****************************************************************************************************/
/* This class represents the bin boundaries in one of several observables                            */
/*                                                                                                   */
/* If constructed with a min a max and a number of bins the bins are constructed automatically with  */
/* equal bin width                                                                                   */
/*                                                                                                   */
/* The first/last bins are under/overflows                                                           */
/*****************************************************************************************************/
#ifndef __OXSX_AXIS__
#define __OXSX_AXIS__
#include <vector>
#include <string>

class PdfAxis{
 public:
    // Equal bin widths
    PdfAxis(const std::string& name_, double min_, double max_, size_t nBins_,
            const std::string& latexName_ = "");


    // Variable width
    PdfAxis(const std::string& name_, const std::vector<double>& lowEdges_, 
            const std::vector<double>& highEdges_, const std::string& latexName_ = "");

    ~PdfAxis() {}

    // Find the Bin value_ is in
    size_t FindBin(double value_) const;

    double GetMin() const {return fMin;}
    double GetMax() const {return fMax;}
    size_t GetNBins() const {return fNBins;}
    double GetBinWidth() const {return fBinWidth;}
    double GetBinLowEdge (size_t i) const {return fBinLowEdges.at(i);}
    double GetBinHighEdge(size_t i) const {return fBinHighEdges.at(i);}
    double GetBinCentre  (size_t i) const {return fBinCentres.at(i);}    
    std::string GetName() const {return fName;}

 private:
    int fNBins;
    double fMin;
    double fMax;
    double fBinWidth;
    std::string fName;
    std::string fLatexName; 
    
    std::vector<double> fBinLowEdges;
    std::vector<double> fBinHighEdges;
    std::vector<double> fBinCentres;
    
};

#endif
