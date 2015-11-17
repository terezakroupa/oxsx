#include <catch.hpp>
#include <DataRepresentation.h>

TEST_CASE("Build from one index"){
    DataRepresentation drep(19);
    REQUIRE(drep.GetLength() == 1);
    REQUIRE(drep.GetIndex(0) == 19);
}

TEST_CASE("Build from vec"){
    std::vector<size_t> indices;
    indices.push_back(5);
    indices.push_back(9);
    indices.push_back(11);

    DataRepresentation drep(indices);
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


TEST_CASE("Looking for the relative indices of 2d rep in 4d rep"){
    std::vector<size_t> smallRepIndices;
    smallRepIndices.push_back(6);
    smallRepIndices.push_back(0);

    std::vector<size_t> bigRepIndices;
    bigRepIndices.push_back(0);
    bigRepIndices.push_back(3);
    bigRepIndices.push_back(6);

    DataRepresentation bigRep(bigRepIndices);
    DataRepresentation smallRep(smallRepIndices);

    std::vector<size_t> relativeIndices = smallRep.GetRelativeIndices(bigRep);

    REQUIRE(relativeIndices.size() == 2);
    REQUIRE(relativeIndices.at(0) == 2);
    REQUIRE(relativeIndices.at(1) == 0);
    
}
