#include <Scale.h>
#include <SystematicExceptions.h>
#include <iostream>

Scale::Scale(unsigned index_){
    SetParameters(std::vector<double>(1,1)); //start with scale factor of one
    fAxisIndex = index_;
}

void 
Scale::SetAxes(const AxisCollection& axes_){
    fPdfMapping.SetAxes(axes_);
}

const AxisCollection& 
Scale::GetAxes() const{
    return fPdfMapping.GetAxes();
}

void 
Scale::Construct(){
    if (GetScaleFactor() <= 0)
        throw InvalidSystematicParameter("Scale factor must be >0 !");

    if (GetParameters().size() != 1)
        throw WrongNumberOfParameters("More than one parameter passed to scale systematic!");
    
    const AxisCollection& axes  = fPdfMapping.GetAxes(); 
    // the axis to scale
    const PdfAxis& scaleAxis    = axes.GetAxis(fDataRep.GetDataIndexPos(fAxisIndex));  
    
    const size_t nBins          = axes.GetNBins(); 
    const size_t scaleAxisNBins = scaleAxis.GetNBins(); 
    const double binWidth       = scaleAxis.GetBinWidth();
 
    std::cout << "In scaler, " << GetScaleFactor() << std::endl;
    for(size_t i = 0; i < nBins; i++){
        // For each old bin, work out the contributions into all of the new bins
        // indicies in other components should be unaffected
        std::vector<size_t> oldIndicies = axes.UnpackIndicies(i);
        size_t scaleBin = oldIndicies.at(fPdfDataRep.GetDataIndexPos(fAxisIndex));
        
        double scaledLow   = scaleAxis.GetBinLowEdge(scaleBin)  * GetScaleFactor();
        double scaledHigh  = scaleAxis.GetBinHighEdge(scaleBin) * GetScaleFactor();
        double scaledWidth = scaledHigh - scaledLow;

        // new bin to map into, mapping only happens if the indicies are the same except the one to 
        // scale so, loop over the bins in the scale axes and leave other indicies the same
        // the others are zero from initialisation 
        
        std::vector<size_t> newIndicies = oldIndicies;
        for(size_t j = 0; j < scaleAxisNBins; j++){
            newIndicies[fPdfDataRep.GetDataIndexPos(fAxisIndex)] = j;
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
                    contribution = 1/GetScaleFactor();

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

void
Scale::SetScaleFactor(double scaleFactor_){
    SetParameter(0, scaleFactor_);
}

double
Scale::GetScaleFactor() const{
    return GetParameter(0);
}

