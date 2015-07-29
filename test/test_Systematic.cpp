#include "../src/systematic/Systematic.h"
#include "../src/pdf/binned/BinnedPdf.h"
#include <TRandom3.h>
#include <iostream>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>

// some of this should be in a pdf test script

class Scale : public Systematic{
public:
    Scale(AxisCollection axes_, double scaleFactor_) : Systematic(axes_), fScaleFactor(scaleFactor_)
    {
        fResponse.resize(fNBins);
        for(size_t i = 0 ; i < fNBins; i++)
            fResponse[i].resize(fNBins, 0);

        for(size_t i = 0; i < fNBins; i++){
            for(size_t j = 0; j < fNBins; j++){
                if(i == j)
                    fResponse[i][j] = scaleFactor_;
            }
        }
    }                                                
private:
    double fScaleFactor;
};

TH1D* ToROOT(BinnedPdf pdf_){
    TH1D* hist = new TH1D("","", 100, -10, 10);
    for(size_t bin = 0; bin < pdf_.GetNBins(); bin++)
        hist->SetBinContent(bin +1, pdf_.GetBinContent(bin));
    return hist;
}


int main(){
    PdfAxis axis("energy", -10, 10, 100, "Energy");
    AxisCollection ac;
    ac.AddAxis(axis);

    // set up a simple gaussian
    BinnedPdf before(ac);
    std::cout << "axis collection dimensions = " << ac.GetNDimensions() << std::endl;
    std::cout << "pdf dimensions = " << before.GetNDims() << std::endl;

    TRandom3 rand;
    TH1D* checkHist = new TH1D("", "", 100, -10 , 10);
    for(unsigned i  = 0; i < 1000; i++){
        double a  = rand.Gaus();
        checkHist -> Fill(a);
        before.Fill(std::vector<double>(1, a));
    }

    TH1D* beforeHist = ToROOT(before);

    Scale scale(ac, 5);
    BinnedPdf after = scale(before, std::vector<size_t> (1,0));

    TH1D* afterHist = ToROOT(after);
    
    TCanvas overlay;
    TLegend leg(0.7, 0.7, 0.9, 0.9);
    leg.AddEntry(beforeHist, "Before");
    leg.AddEntry(afterHist, "After");
    afterHist->SetLineColor(2);
    afterHist->SetLineStyle(2);

    overlay.cd();
    afterHist->Draw();
    beforeHist->Draw("same");
    overlay.SaveAs("test_Systematic.root");
    return 0;
}
