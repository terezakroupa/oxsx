#include <catch.hpp>
#include <Cut.h>

TEST_CASE("1D cut"){
    Cut cut(0);
    cut.SetLowerLimit(1);
    cut.SetUpperLimit(10);
    
    SECTION("in the middle of accepted range"){
        EventData ev(std::vector<double>(1, 5));
        REQUIRE(cut.PassesCut(ev) == true);
    }

    SECTION("below accepted range"){
        EventData ev(std::vector<double>(1, 0));
        REQUIRE(cut.PassesCut(ev) == false);
    }

    SECTION("above accepted range"){
        EventData ev(std::vector<double>(1, 11));
        REQUIRE(cut.PassesCut(ev) == false);
    }

    SECTION("on lower boundary"){
        EventData ev(std::vector<double>(1, 1));
        REQUIRE(cut.PassesCut(ev) == false);
    }

    SECTION("on upper boundary"){
        EventData ev(std::vector<double>(1, 10));
        REQUIRE(cut.PassesCut(ev) == false);
    }
}
