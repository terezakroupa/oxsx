#include <Scale.h>

void 
Scale::SetAxes(const AxisCollection& axes_){
    fPdfMapping.SetAxes(axes_);
    Construct();
}

const AxisCollection& 
Scale::GetAxes() const{
    return fPdfMapping.GetAxes();
}


void 
Scale::Construct(){
    if (fScaleFactor <= 0)
        throw 0; //FIXME

    const AxisCollection& axes  = fPdfMapping.GetAxes(); 
    const PdfAxis& scaleAxis    = axes.GetAxis(fAxisIndex);  // the axis to scale

    const size_t nBins          = axes.GetNBins(); 
    const size_t scaleAxisNBins = scaleAxis.GetNBins(); 
    const double binWidth       = scaleAxis.GetBinWidth();
 
    for(size_t i = 0; i < nBins; i++){
        // For each old bin, work out the contributions into all of the new bins
        // indicies in other components should be unaffected

        std::vector<size_t> oldIndicies = axes.UnpackIndicies(i);
        size_t scaleBin = oldIndicies.at(fAxisIndex);
        
        double scaledLow   = scaleAxis.GetBinLowEdge(scaleBin)  * fScaleFactor;
        double scaledHigh  = scaleAxis.GetBinHighEdge(scaleBin) * fScaleFactor;
        double scaledWidth = scaledHigh - scaledLow;

        // new bin to map into, mapping only happens if the indies are the same except the one to scale
        // so, loop over the bins in the scale axes and leave other indicies the same
        // the others are zero from initialisation 
        
        std::vector<size_t> newIndicies = oldIndicies;
        for(size_t j = 0; j < scaleAxisNBins; j++){
            newIndicies[fAxisIndex] = j;
            size_t newScaleBin = j;
                        
            double newLow  = scaleAxis.GetBinLowEdge(newScaleBin);
            double newHigh = scaleAxis.GetBinHighEdge(newScaleBin);

            double contribution;
            // Is it in the scale region at all?
            if (newLow > scaledHigh || newHigh < scaledLow) 
                contribution = 0;

            else{
                // Is it fully in the region?
                bool includedFromBelow = newLow > scaledLow;
                bool includedFromAbove = newHigh < scaledHigh;

                if (includedFromBelow && includedFromAbove) 
                    // fully inside
                    contribution = 1/fScaleFactor;

                else if (includedFromBelow) 
                    // spills partly over the top
                    contribution = (scaledHigh - newLow)/scaledWidth;

                else 
                    // spills partly over the bottom
                    contribution = (newHigh - scaledLow)/scaledWidth;
                
            }
            
            fPdfMapping.SetComponent(axes.FlattenIndicies(newIndicies), i, contribution);
            
        }
               
    }
    return;
}
