#include <BinnedPdf.h>
#include <CompositePdf.h>
#include <Gaussian.h>
#include <ROOTNtuple.h>
#include <PdfConverter.h>
#include <iostream>

int main(){
    // Set Up binning
    AxisCollection axes;
    axes.AddAxis(PdfAxis("energy", 2, 3, 10, "Energy"));            // min, max, nbins
    
    // custom radial bins as vec
    std::vector<double> radialBinLows(10);
    std::vector<double> radialBinHighs(10);
    for(size_t i = 0; i < radialBinLows.size(); i++){
        radialBinLows[i] = 0.1 * i;
        radialBinHighs[i] = 0.1 * i + 0.05;
    }
    
    axes.AddAxis(PdfAxis("radius", radialBinLows, radialBinHighs, "$\rho$"));

    BinnedPdf energyRadiusPdf(axes);
    
    // Tell the pdf where it looks in the data - the first two indicies in the ntuples
    std::vector<size_t> indicies;
    indicies.push_back(0);
    indicies.push_back(1);
    energyRadiusPdf.SetDataRep(DataRepresentation(indicies));
    

    // fill from mc data
    ROOTNtuple twoNuMC("/Users/Jack/snoplus/sigEx/ntuples/rat4.5/exyzt/zeroNu.root", "oxsx");

    for(size_t i = 0; i < twoNuMC.GetNEntries(); i++){
        EventData evData = twoNuMC.GetEntry(i);
        energyRadiusPdf.Fill(evData);                // pdf knows where to look
    }
    energyRadiusPdf.Normalise();

    // Make analytic approximation in a third variable, say PSD
    Gaussian psdGaus(0.5, 1); // mean,sigma
    
    // Turn it into a binned pdf looking at index 2
    AxisCollection psdAxes;
    psdAxes.AddAxis(PdfAxis("psd", -2, 2, 10));
    
    DataRepresentation psdRep(std::vector<size_t>(1, 2));


    BinnedPdf psdPDF = PdfConverter::ToBinnedPdf(psdGaus, psdAxes);
    psdPDF.SetDataRep(psdRep);


    // Combine the two into a new pdf
    CompositePdf finalPdf = energyRadiusPdf * psdPDF;


    // index manipulations done automatically
    std::cout << finalPdf.Probability(twoNuMC.GetEntry(0)) << std::endl;

    return 0;
}
