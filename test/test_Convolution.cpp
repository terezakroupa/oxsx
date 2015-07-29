#include "../src/pdf/IntegrablePdf.h"
#include "../src/pdf/analytic/Gaussian.h"
#include "../src/systematic/Convolution.h"
#include "../src/pdf/binned/AxisCollection.h"
#include "../src/pdf/binned/BinnedPdf.h"
#include <TRandom3.h>
#include <TH1D.h>
#include <TFile.h>
#include <iostream>

TH1D* ToROOT(BinnedPdf pdf_){
    TH1D* hist = new TH1D("","", 200, -20, 20);
    for(size_t bin = 0; bin < pdf_.GetNBins(); bin++)
        hist->SetBinContent(bin +1, pdf_.GetBinContent(bin));
    return hist;
}

int main(){
    
    AxisCollection axes;
    PdfAxis energyAxis("energy", -20, 20, 200, "Energy");
    axes.AddAxis(energyAxis);
    BinnedPdf preSmear(axes);

    Gaussian gaussianPdf(0.5, 4);
    std::cout << gaussianPdf.Integral(std::vector<double>(1,-3.5), std::vector<double>(1,4.5))
              << std::endl;
    Convolution systematic;
    systematic.SetPdf(&gaussianPdf);
    systematic.SetAxes(axes);
    
    TRandom3 rand;
    for(unsigned i = 0; i < 100000; i++)
        // pythragorean triples, expect a resulting width of 5 and mean of 1.3...
        preSmear.Fill(std::vector<double>(1,rand.Gaus(1.2,3))); 


    BinnedPdf afterSmear = systematic(preSmear, std::vector<size_t> (1,0));


    TFile outFile("convolution_test.root", "RECREATE");
    TH1D* before = ToROOT(preSmear);
    TH1D* after  = ToROOT(afterSmear);

    before -> Write();
    after  -> Write();
    return 0;
}
