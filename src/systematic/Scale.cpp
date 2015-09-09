#include <Scale.h>

BinnedPdf
Scale::operator()(const BinnedPdf& pdf_, const std::vector<size_t>& indicies_) const{
    // Bypass the detector response for this simple calculation for speed
    BinnedPdf scaled(pdf_);
    scaled.Empty();
    for(size_t bin = 0; bin < pdf_.GetNBins(); bin++){
        scaled.AddBinContent(bin, fScaleFactor * pdf_.GetBinContent(bin));
    }
    return scaled;
}

