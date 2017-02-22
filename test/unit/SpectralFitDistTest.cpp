#include <catch.hpp>
#include <SpectralFitDist.h>

TEST_CASE(""){    
    AxisCollection axes;
    axes.AddAxis(BinAxis("test1", 0, 10, 10));
    axes.AddAxis(BinAxis("test2", 0, 10, 10));

    SpectralFitDist fitED(axes);
    
    SECTION("Behaves like a binned pdf"){
        REQUIRE(fitED.GetNDims() == 2);
        REQUIRE(fitED.GetNBins() == 100);
        REQUIRE(fitED.GetBinContents() == std::vector<double>(100, 0));
    }
    SECTION("Bin contents are adjustable"){
        fitED.MakeFittable();
        REQUIRE(fitED.GetParameterCount() == 100);
        REQUIRE(fitED.GetParameters() == std::vector<double>(100, 0));

        std::vector<double> testConts;
        testConts.reserve(100);
        for(int i = 0; i < 100; i++){
            testConts.push_back(i);                        
        }
        fitED.SetParameters(testConts);
        REQUIRE(fitED.GetParameters() == testConts);
        REQUIRE(fitED.GetBinContents() == testConts);        
    }
    
}
