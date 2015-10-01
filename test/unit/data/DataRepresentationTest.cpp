#include <catch.hpp>
#include <DataRepresentation.h>

TEST_CASE("Build from one index"){
    DataRepresentation drep(19);
    REQUIRE(drep.GetLength() == 1);
    REQUIRE(drep.GetIndex(0) == 19);
}

TEST_CASE("Build from vec"){
    std::vector<size_t> indicies;
    indicies.push_back(5);
    indicies.push_back(9);
    indicies.push_back(11);

    DataRepresentation drep(indicies);
    REQUIRE(drep.GetLength() == 3);
    REQUIRE(drep.GetIndex(0) == 5);
    REQUIRE(drep.GetIndex(1) == 9);
    REQUIRE(drep.GetIndex(2) == 11);

    SECTION("Then copy construct"){
        DataRepresentation drep2(drep);
        REQUIRE(drep2.GetLength() == 3);
        REQUIRE(drep2.GetIndex(0) == 5);
        REQUIRE(drep2.GetIndex(1) == 9);
        REQUIRE(drep2.GetIndex(2) == 11);
        
    }

    SECTION("Testing Inverse Functionality"){
        REQUIRE(drep.GetDataIndexPos(11) == 2);
        REQUIRE(drep.GetDataIndexPos(5) == 0);
        REQUIRE(drep.GetDataIndexPos(9) == 1);
    }


}


TEST_CASE("Looking for the relative indicies of 2d rep in 4d rep"){
    std::vector<size_t> smallRepIndicies;
    smallRepIndicies.push_back(6);
    smallRepIndicies.push_back(0);

    std::vector<size_t> bigRepIndicies;
    bigRepIndicies.push_back(0);
    bigRepIndicies.push_back(3);
    bigRepIndicies.push_back(6);

    DataRepresentation bigRep(bigRepIndicies);
    DataRepresentation smallRep(smallRepIndicies);

    std::vector<size_t> relativeIndicies = smallRep.GetRelativeIndicies(bigRep);

    REQUIRE(relativeIndicies.size() == 2);
    REQUIRE(relativeIndicies.at(0) == 2);
    REQUIRE(relativeIndicies.at(1) == 0);
    
}
