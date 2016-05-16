#include <BayesianUpperBound.h>
#include <Exceptions.h>
#include <Histogram.h>
#include <iostream>

double
BayesianUpperBound::Evaluate(const Histogram& posterior_){
    // Makes no sense for an empty histogram
    if(!posterior_.Integral())
        throw ValueError("BayesianUpperBound::Empty histogram passed!");
    
    if(fCl <= 0)
        throw ValueError(Formatter() << "BayesianUpperBound:: cl = " << fCl
                         << " , must be >0!");
    
    // only works for 1D histograms currently
    if(posterior_.GetNDims() != 1)
        throw DimensionError("BayesIntervalCal", 1, posterior_.GetNDims(), 
                             "Only implemented for 1D, marginalise?");


    // Integrate from the minimum to x until the total probability exceeds fCl
    // find the first bin <b> for which the integral  <0>-><b> > cl
    int    critBin  = 0;
    double integral = 0;
    double sum = 0;
    while(true){
        sum = 0;              
        for(size_t i = 0; i < critBin; i++){
            sum += posterior_.GetBinContent(i);
        }
        if (sum < fCl)
            critBin++;
        else
            break;
        
    }

    // now interpolate between the bins    
    double upperEdge = posterior_.GetAxes().GetBinHighEdge(critBin, 0);
    double lowerEdge = posterior_.GetAxes().GetBinLowEdge(critBin, 0);
    double content   = posterior_.GetBinContent(critBin);

    return upperEdge - (upperEdge - lowerEdge) * (sum - fCl)/content;
         
}
