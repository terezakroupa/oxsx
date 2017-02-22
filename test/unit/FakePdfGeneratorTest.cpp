#include <catch.hpp>
#include <FakePdfGenerator.h>
#include <Gaussian.h>
#include <PdfConverter.h>
#include <cmath>

TEST_CASE("Recover a 1D gaussian"){
    Gaussian gaus(0, 10);
    AxisCollection axes;
    axes.AddAxis(PdfAxis("test", -100, 100, 200));
    
    BinnedPdf inPdf  = PdfConverter::ToBinnedPdf(gaus, axes);
    
    FakePdfGenerator pdfGen;
    pdfGen.SetRates(std::vector<double> (1, 1000000));
    pdfGen.SetPdfs(std::vector<BinnedPdf> (1, inPdf));

    BinnedPdf outPdf = pdfGen.ExpectedRatesPdf();
    REQUIRE(outPdf.Integral() == 1000000);
    outPdf.Normalise();

    double outMean = outPdf.Means().at(0);
    double inMean = inPdf.Means().at(0);

    REQUIRE(std::abs(outMean) < 0.01);
}
