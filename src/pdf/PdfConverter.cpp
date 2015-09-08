#include <PdfConverter.h>
#include <BinnedPdf.h>
#include <IntegrablePdf.h>
#include <AxisCollection.h>
#include <vector>

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
