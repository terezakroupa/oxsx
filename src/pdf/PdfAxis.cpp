#include "PdfAxis.h"
#include <algorithm>

PdfAxis::PdfAxis(const std::string& name_, double min_, double max_, size_t nBins_,
                 const std::string& latexName_){
    fName = name_;
    fLatexName = latexName_;
    if(fLatexName == "")
        fLatexName = name_;
    fMin = min_;
    fMax = max_;
    fNBins = nBins_;
    fBinWidth =  double(fMax - fMin) /fNBins;

    fBinLowEdges.resize(fNBins, 0);    
    fBinHighEdges.resize(fNBins, 0);
    for(size_t i = 0; i < fNBins; i++){
        fBinLowEdges[i]  = fMin  + i     * fBinWidth;
        fBinHighEdges[i] = fMin  + (i+1) * fBinWidth;
    }
}

size_t PdfAxis::FindBin(double value_) const{
    size_t insertIndex = std::lower_bound(fBinHighEdges.begin(), fBinHighEdges.end(), value_) - 
        fBinHighEdges.begin();
    if (insertIndex == fNBins)
        return insertIndex-1;
    return insertIndex;
}
