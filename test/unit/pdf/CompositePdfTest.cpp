#include <catch.hpp>
#include <Gaussian.h>
#include <BinnedPdf.h>
#include <CompositePdf.h>
#include <iostream>

TEST_CASE("Combining 1D gaussians", "[CompositePdf]"){

    Gaussian gaus1(0.5, 0.4);
    Gaussian gaus2(0.5, 0.3);

    DataRepresentation d1(0);
    DataRepresentation d2(2);
    

    gaus1.SetDataRep(d1);

    gaus2.SetDataRep(d2);

    CompositePdf compositePdf = gaus1 * gaus2;

    // test values
    std::vector<double> vals;
    vals.push_back(1);
    vals.push_back(999);
    vals.push_back(1);
    vals.push_back(1);
    vals.push_back(999);



    SECTION("Check Dimensions"){
        REQUIRE(compositePdf.GetNDims() == 2);
    }

    SECTION("Check Data Flow to internal pdfs "){

        double prob  = compositePdf.Probability(EventData(vals));
        REQUIRE(prob == Approx(0.15141173681343614));
        
    }

    SECTION("Check Clone Functionality"){
        Pdf* clone = compositePdf.Clone();
        REQUIRE(clone -> GetNDims() == 2);
        REQUIRE(clone -> Probability(EventData(vals)) == Approx(0.15141173681343614));
    }

    SECTION("Second level of recursion"){
        Gaussian nextPdf = Gaussian(0.9, 0.8);
        nextPdf.SetDataRep(DataRepresentation(3));
        CompositePdf level2 = compositePdf * nextPdf;
        REQUIRE( level2.GetNDims() == 3 );
        REQUIRE( level2.Probability(EventData(vals)) == Approx(0.07491808959564718));
                                                                                         
    }
}

TEST_CASE(" Composite of two Binned Pdfs"){

    // Paired into two couplets
    PdfAxis axis1("axis1", -80, 80, 100);
    PdfAxis axis2("axis2", -80, 80, 100);

    PdfAxis axis3("axis3", -80, 80, 100);
    PdfAxis axis4("axis4", -80, 80, 100);

    AxisCollection axes1;
    AxisCollection axes2;
    
    axes1.AddAxis(axis1);
    axes1.AddAxis(axis2);
    
    axes2.AddAxis(axis3);
    axes2.AddAxis(axis4);

    BinnedPdf pdf1(axes1);
    BinnedPdf pdf2(axes2);


    // Data, where to look
    std::vector<size_t> indicies1;
    std::vector<size_t> indicies2;

    indicies1.push_back(0);
    indicies1.push_back(2);
    
    indicies2.push_back(1);
    indicies2.push_back(3);

    pdf1.SetDataRep(indicies1);
    pdf2.SetDataRep(indicies2);

    // Now combine
    CompositePdf compositePdf = pdf1 * pdf2;


}

