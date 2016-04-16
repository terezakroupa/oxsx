#include <catch.hpp>
#include <BinnedPdfManager.h>
#include <PdfConverter.h>
#include <Gaussian.h>
#include <iostream>

TEST_CASE("Three pdfs no systematics"){
    Gaussian gaus1(0, 1);
    Gaussian gaus2(2, 3);
    Gaussian gaus3(4, 5);

    AxisCollection axes;
    axes.AddAxis(PdfAxis("axis1", -40, 40 , 200));

    BinnedPdf pdf1 = PdfConverter::ToBinnedPdf(gaus1, axes);
    BinnedPdf pdf2 = PdfConverter::ToBinnedPdf(gaus2, axes);
    BinnedPdf pdf3 = PdfConverter::ToBinnedPdf(gaus3, axes);

    pdf1.SetDataRep(0);
    pdf2.SetDataRep(0);    
    pdf3.SetDataRep(0);

    double prob1 = pdf1.GetBinContent(0);
    double prob2 = pdf2.GetBinContent(0);    
    double prob3 = pdf3.GetBinContent(0);

    BinnedPdfManager pdfMan;
    pdfMan.AddPdf(pdf1);
    pdfMan.AddPdf(pdf2);
    pdfMan.AddPdf(pdf3);
    pdfMan.SetNormalisations(std::vector<double>(3, 1));

    SECTION("Bin Probability Method"){
        REQUIRE(pdfMan.BinProbability(0) == Approx(prob1 * prob2 * prob3));
    }
    
    SECTION("Probability Method"){
        REQUIRE(pdfMan.Probability(EventData(std::vector<double>(1, -39.5))) == Approx(prob1 * prob2 * prob3));
    }

}
