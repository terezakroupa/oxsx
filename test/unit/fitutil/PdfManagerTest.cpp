#include <catch.hpp>
#include <PdfManager.h>
#include <Gaussian.h>
#include <AnalyticPdf.h>
#include <EventData.h>

TEST_CASE("Add a couple of analytic pdfs"){
    PdfManager pdfMan;
    Gaussian gaus1(0, 1);
    Gaussian gaus2(0, 1);

    AnalyticPdf pdf1(&gaus1);
    AnalyticPdf pdf2(&gaus2);
    pdf1.SetDataRep(0);
    pdf2.SetDataRep(0);
    
    SECTION("initialised correctly"){
        REQUIRE(pdfMan.GetNPdfs() == 0);
        REQUIRE(pdfMan.GetNDims() == 0);
        
    }
    
    SECTION("add pdfs one at a time"){
        pdfMan.AddPdf(&pdf1);
        pdfMan.AddPdf(&pdf2);
        
        REQUIRE(pdfMan.GetNDims() == 1);
        REQUIRE(pdfMan.GetNPdfs() == 2);
        REQUIRE(pdfMan.GetNormalisations() == std::vector<double>(2, 0));
    }
    
    SECTION("add pdfs in one go"){
        std::vector<Pdf*> pdfs;
        pdfs.push_back(&pdf1);
        pdfs.push_back(&pdf2);
        pdfMan.AddPdfs(pdfs);
        
        REQUIRE(pdfMan.GetNDims() == 1);
        REQUIRE(pdfMan.GetNPdfs() == 2);
        REQUIRE(pdfMan.GetNormalisations() == std::vector<double>(2, 0));
    }

    SECTION("correct probability"){
        pdfMan.AddPdf(&pdf1);
        pdfMan.AddPdf(&pdf2);

        EventData event(std::vector<double>(1, 0));
        REQUIRE(pdfMan.Probability(event) == 0); // norms are zero

        pdfMan.SetNormalisations(std::vector<double>(2, 1));
        REQUIRE(pdfMan.Probability(event) == Approx(0.7978845607));
        // 0.7978845607 = 2 /sqrt(2 * pi)
    }

    SECTION("works as fit component"){
        pdfMan.AddPdf(&pdf1);
        pdfMan.AddPdf(&pdf2);
        pdfMan.MakeFittable();

        REQUIRE(pdfMan.GetParameterCount() == 2);
        REQUIRE(pdfMan.GetParameterValues() == std::vector<double>(2, 0));
        
        std::vector<std::string> expectedNames;
        expectedNames.push_back("Pdf Normalisation 0");
        expectedNames.push_back("Pdf Normalisation 1");
        REQUIRE(pdfMan.GetParameterNames() == expectedNames);
        
        std::vector<double> newParameters(2, 10);
        pdfMan.SetParameterValues(newParameters);
        REQUIRE(pdfMan.GetParameterValues() == newParameters);
        REQUIRE(pdfMan.GetNormalisations() == newParameters);
    }
}
