#include <PdfConverter.h>
#include <BinnedPdf.h>
#include <IntegrablePdf.h>
#include <AxisCollection.h>
#include <vector>
#include <PdfExceptions.h>

BinnedPdf
PdfConverter::ToBinnedPdf(const IntegrablePdf& analytic_, const AxisCollection& axes_){
    if (analytic_.GetNDims() != axes_.GetNDimensions())
        throw DimensionError("PdfConverter::Dimensionality of Pdf doesn't match requested axes!");

    BinnedPdf binnedPdf(axes_);
    // Loop over bins
    for(size_t bin = 0; bin < axes_.GetNBins(); bin++){
        std::vector<double> lows  = axes_.GetBinLowEdges(bin);
        std::vector<double> highs = axes_.GetBinHighEdges(bin);

        binnedPdf.AddBinContent(bin, analytic_.Integral(lows, highs));
    }
    
    return binnedPdf;
}

TH1D
PdfConverter::ToTH1D(const BinnedPdf& pdf_){
    if(pdf_.GetNDims() != 1)
        throw DimensionError("Only a 1D pdf can be represented by a TH1D");
 
    const PdfAxis& axis  = pdf_.GetAxes().GetAxis(0);
    const unsigned nBins = axis.GetNBins(); 
    TH1D rtHist("", "", nBins, axis.GetBinLowEdge(0), axis.GetBinHighEdge(nBins - 1));
    rtHist.SetDirectory(0);

    for(unsigned bin = 0; bin < nBins; bin++)
        rtHist.SetBinContent(bin+1, pdf_.GetBinContent(bin));
    
    return rtHist;                         
}
