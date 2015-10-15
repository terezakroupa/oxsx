#include <catch.hpp>
#include <BinnedPdfShrinker.h>

TEST_CASE("Shrinking a single uniform Pdf Axis"){
    PdfAxis axis("test", 0, 100, 100, "latexnametest");
    BinnedPdfShrinker shrinker(1);
    PdfAxis shrunkAxis = shrinker.ShrinkAxis(axis, 2, 3);
    
    REQUIRE(shrunkAxis.GetNBins() == axis.GetNBins() - 5);
    
    

}
