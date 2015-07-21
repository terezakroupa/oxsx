#ifndef __AXIS__
#define __AXIS__
#include <vector>
#include <string>

class PdfAxis{
 public:
    // Construct the bins
    PdfAxis(const std::string& name_, double min_, double max_, size_t nBins_,
            const std::string& latexName_ = "");
    
    // Find the correct bin
    size_t FindBin(double value_) const;

    double GetMin() const {return fMin;}
    double GetMax() const {return fMax;}
    size_t GetNBins() const {return fNBins;}
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
        
};

#endif
