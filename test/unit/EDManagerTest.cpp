#include <catch.hpp>
#include <EDManager.h>
#include <Gaussian.h>
#include <AnalyticED.h>
#include <Event.h>

TEST_CASE("Add a couple of analytic pdfs"){
    EDManager pdfMan;
    Gaussian gaus1(0, 1);
    Gaussian gaus2(0, 1);

    AnalyticED pdf1(&gaus1);
    AnalyticED pdf2(&gaus2);
    pdf1.SetObservables(0);
    pdf2.SetObservables(0);
    
    SECTION("initialised correctly"){
        REQUIRE(pdfMan.GetNDists() == 0);
        REQUIRE(pdfMan.GetNDims() == 0);
        
    }
    
    SECTION("add pdfs one at a time"){
        pdfMan.AddDist(&pdf1);
        pdfMan.AddDist(&pdf2);
        
        REQUIRE(pdfMan.GetNDims() == 1);
        REQUIRE(pdfMan.GetNDists() == 2);
        REQUIRE(pdfMan.GetNormalisations() == std::vector<double>(2, 0));
    }
    
    SECTION("add dists in one go"){
        std::vector<EventDistribution*> dists;
        dists.push_back(&pdf1);
        dists.push_back(&pdf2);
        pdfMan.AddDists(dists);
        
        REQUIRE(pdfMan.GetNDims() == 1);
        REQUIRE(pdfMan.GetNDists() == 2);
        REQUIRE(pdfMan.GetNormalisations() == std::vector<double>(2, 0));
    }

    SECTION("correct probability"){
        pdfMan.AddDist(&pdf1);
        pdfMan.AddDist(&pdf2);

        Event event(std::vector<double>(1, 0));
        REQUIRE(pdfMan.Probability(event) == 0); // norms are zero

        pdfMan.SetNormalisations(std::vector<double>(2, 1));
        REQUIRE(pdfMan.Probability(event) == Approx(0.7978845607));
        // 0.7978845607 = 2 /sqrt(2 * pi)
    }

    SECTION("works as fit component"){
        pdfMan.AddDist(&pdf1);
        pdfMan.AddDist(&pdf2);
        pdfMan.MakeFittable();

        REQUIRE(pdfMan.GetParameterCount() == 2);
        REQUIRE(pdfMan.GetParameters() == std::vector<double>(2, 0));
        
        std::vector<std::string> expectedNames;
        expectedNames.push_back("Dist Normalisation 0");
        expectedNames.push_back("Dist Normalisation 1");
        REQUIRE(pdfMan.GetParameterNames() == expectedNames);
        
        std::vector<double> newParameters(2, 10);
        pdfMan.SetParameters(newParameters);
        REQUIRE(pdfMan.GetParameters()     == newParameters);
        REQUIRE(pdfMan.GetNormalisations() == newParameters);
    }
}
