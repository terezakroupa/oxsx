#include <catch.hpp>
#include <HistTools.h>
#include <BinAxis.h>
#include <Histogram.h>
#include <Combinations.hpp>
#include <Formatter.hpp>

TEST_CASE("Producing  histograms from a set of axes"){    
    // make the axes
    AxisCollection axes;
    std::stringstream ss;
    for(int i = 0; i < 4; i++)
        axes.AddAxis(BinAxis(Formatter() << i, 0, 1, 1));
    
    std::vector<std::string> dimensionList = axes.GetAxisNames();


    SECTION("2D"){
        std::vector<std::pair<std::string, std::string> >l2combinations =  Combinations::AllCombsNoDiag<std::string>(dimensionList);
        
        std::vector<Histogram> hists = HistTools::MakeAllHists(axes, l2combinations);
        for(size_t i = 0; i < hists.size(); i++){
            REQUIRE(hists.at(i).GetAxes().GetAxis(0).GetName() == l2combinations.at(i).first);
            REQUIRE(hists.at(i).GetAxes().GetAxis(1).GetName() == l2combinations.at(i).second);
        }
    
    }
    
    SECTION("1D"){
        std::vector<Histogram> hists = HistTools::MakeAllHists(axes, dimensionList);
        for(size_t i = 0; i < hists.size(); i++){
            REQUIRE(hists.at(i).GetAxes().GetAxis(0).GetName() == dimensionList.at(i));
        }
    }
        
}
    

