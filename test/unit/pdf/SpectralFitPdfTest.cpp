#include <catch.hpp>
#include <SpectralFitPdf.h>

TEST_CASE(""){    
    AxisCollection axes;
    axes.AddAxis(PdfAxis("test1", 0, 10, 10));
    axes.AddAxis(PdfAxis("test2", 0, 10, 10));

    SpectralFitPdf fitPdf(axes);
    
    SECTION("Behaves like a binned pdf"){
        REQUIRE(fitPdf.GetNDims() == 2);
        REQUIRE(fitPdf.GetNBins() == 100);
        REQUIRE(fitPdf.GetBinContents() == std::vector<double>(100, 0));
    }
    SECTION("Bin contents are adjustable"){
        fitPdf.MakeFittable();
        REQUIRE(fitPdf.GetParameterCount() == 100);
        REQUIRE(fitPdf.GetParameterValues() == std::vector<double>(100, 0));

        std::vector<double> testConts;
        testConts.reserve(100);
        for(int i = 0; i < 100; i++){
            testConts.push_back(i);                        
        }
        fitPdf.SetParameterValues(testConts);
        REQUIRE(fitPdf.GetParameterValues() == testConts);
        REQUIRE(fitPdf.GetBinContents() == testConts);        
    }
    
}
