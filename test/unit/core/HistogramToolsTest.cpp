#include <catch.hpp>
#include <HistTools.h>
#include <PdfAxis.h>
#include <Histogram.h>
#include <Combinations.hpp>
#include <Formatter.hpp>

TEST_CASE("Producing all the possible 2D histograms from a set of axes"){    
    // make the axes
    std::vector<PdfAxis> axes;
    std::stringstream ss;
    for(int i = 0; i < 10; i++){
        axes.push_back(PdfAxis(Formatter() << i, 0, 1, 1));
    }
    
    std::vector<size_t> dimensionList = SequentialElements<size_t>(size_t(0), axes.size());
    std::vector<std::vector<size_t> > l2combinations = FixedLengthCombinationsNoDuplicates<size_t>(dimensionList, 2);

    std::vector<Histogram> hists = HistTools::MakeAllHists(axes, l2combinations);
    for(size_t i = 0; i < hists.size(); i++){
        for(size_t j = 0; j < hists.at(i).GetNDims(); j++){
            REQUIRE(hists.at(i).GetAxes().GetAxis(j).GetName() == std::string(Formatter() << l2combinations.at(i).at(j)));
        }
    }
    
}
