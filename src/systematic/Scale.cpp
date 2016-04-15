#include <Scale.h>
#include <DoubleParameter.h>
#include <PdfExceptions.h>
#include <DataExceptions.h>
#include <sstream>

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
    if (fScaleFactor <= 0)
        throw ParameterError("Scale factor must be >0 !");
    
    if(fDataRep.GetNObservables() != 1)
        throw RepresentationError("Scale systematic must have a 1D representation!");

    const AxisCollection& axes       = fPdfMapping.GetAxes(); 
    // the axis to scale
    const size_t  scaleAxisDataIndex = fDataRep.GetIndex(0);
    const PdfAxis& scaleAxis         = axes.GetAxis(scaleAxisDataIndex);


    const size_t nBins               = axes.GetNBins(); 
    const size_t scaleAxisNBins      = scaleAxis.GetNBins(); 
 
    for(size_t i = 0; i < nBins; i++){
        // For each old bin, work out the contributions into all of the new bins
        // indices in other components should be unaffected
        std::vector<size_t> oldIndices = axes.UnpackIndices(i);
        size_t scaleBin                = oldIndices.at(fPdfDataRep.GetDataIndexPos(scaleAxisDataIndex));
        
        double scaledLow   = scaleAxis.GetBinLowEdge(scaleBin)  * fScaleFactor;
        double scaledHigh  = scaleAxis.GetBinHighEdge(scaleBin) * fScaleFactor;
        double scaledWidth = scaledHigh - scaledLow;

        // new bin to map into, mapping only happens if the indices are the same except the one to 
        // scale so, loop over the bins in the scale axes and leave other indices the same
        // the others are zero from initialisation 
        
        std::vector<size_t> newIndices = oldIndices;
        for(size_t j = 0; j < scaleAxisNBins; j++){
            newIndices[fPdfDataRep.GetDataIndexPos(scaleAxisDataIndex)] = j;
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
            
            fPdfMapping.SetComponent(axes.FlattenIndices(newIndices), i, contribution);
        }
               
    }
    return;
}

void
Scale::SetScaleFactor(double scaleFactor_){
    fScaleFactor = scaleFactor_;
}

double
Scale::GetScaleFactor() const{
    return fScaleFactor;
}


//////////////////////////////////////////////////////////////////
// Make this object fittable, so the scale factor is adjustable //
//////////////////////////////////////////////////////////////////

void
Scale::MakeFittable(){
    EmptyParameters();
    std::stringstream ss;
    ss << "Scale factor on axis " << fDataRep.GetIndex(0);
    AddAsParameter(new DoubleParameter(fScaleFactor), ss.str());
}
