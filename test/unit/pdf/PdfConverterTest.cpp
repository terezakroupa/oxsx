#include <catch.hpp>
#include <PdfConverter.h>
#include <BinnedPdf.h>
#include <Gaussian.h>
#include <TRandom3.h>
#include <TFitResultPtr.h>
#include <TFitResult.h>

TEST_CASE("Writing a 1D pdf to a root histogram"){
    PdfAxis axis("test", -100, 100, 200);
    AxisCollection axes;
    axes.AddAxis(axis);

    BinnedPdf binnedPdf(axes);

    SECTION("Step Function pdf"){
        // fill a heaviside
        for(size_t i = 0; i < 200; i++){
            if(binnedPdf.GetAxes().GetBinLowEdge(i, 0) >= 0)
                binnedPdf.SetBinContent(i,1);
        }

        TH1D rootPdf = PdfConverter::ToTH1D(binnedPdf);
        REQUIRE(rootPdf.Integral() == 100);
        

        // root histograms are ordered 1->nbins with 0 and nbins +1 as over/underflow
        // nativex pdfs are ordered 0->nbins-1 with 0 and nbins-1 as underflow

        std::vector<double> firstOneHundred;
        for(size_t i = 1; i < 101; i++)
            firstOneHundred.push_back(rootPdf.GetBinContent(i));

        std::vector<double> secondOneHundred;
        for(size_t i = 101; i < 201; i++)
            secondOneHundred.push_back(rootPdf.GetBinContent(i));

        double underflow = rootPdf.GetBinContent(0);
        double overflow  = rootPdf.GetBinContent(201);


        REQUIRE(firstOneHundred == std::vector<double>(100, 0));
        REQUIRE(secondOneHundred == std::vector<double>(100, 1));
        REQUIRE(underflow == 0);
        REQUIRE(overflow == 0);
    }

}

TEST_CASE("Converting a 1D gaussian to a binned pdf"){
    PdfAxis axis("test", -100, 100, 2000);
    AxisCollection axes;
    axes.AddAxis(axis);

    Gaussian gaus(10, 21.1);
    BinnedPdf binnedGaus = PdfConverter::ToBinnedPdf(gaus, axes);           

    SECTION("Numerical Checks"){
        REQUIRE(binnedGaus.Integral() == 1);
        REQUIRE(binnedGaus.Means().at(0) == Approx(10));
        REQUIRE(binnedGaus.Variances().at(0) == Approx(21.1));
    }

    SECTION("Writing the Gaussian to root"){
        TH1D rootPdf = PdfConverter::ToTH1D(binnedGaus);
    }   
}
    
