#include <catch.hpp>
#include "TestComponent.h"
#include <list>
#include <vector>
#include <iostream>

    
TEST_CASE("Do parameters register correctly?"){
    TestComponent tComp;
    tComp.MakeFittable();

    SECTION("Parameter values"){
        REQUIRE(tComp.GetParameterCount() == 21);
        REQUIRE(tComp.GetParameterValues() == std::vector<double>(21, 0));
    }
    SECTION("Parameter Names"){
        std::vector<std::string> expectedNames(1, "double");    
        for(size_t i = 0; i < tComp.fListParameters.size(); i++){
            std::stringstream ss;
            ss << "list " << i;
            expectedNames.push_back(ss.str());
        }

        for(size_t i = 0; i < tComp.fVectorParameters.size(); i++){
            std::stringstream ss;
            ss << "vector " << i;
            expectedNames.push_back(ss.str());
        }
        REQUIRE(tComp.GetParameterNames() == expectedNames);

    }

    SECTION("after copy"){
        TestComponent tCompCopy(tComp);
        REQUIRE(tCompCopy.GetParameterCount() == 0);
        tCompCopy.MakeFittable();
        REQUIRE(tCompCopy.GetParameterCount() == 21);
    }

}

TEST_CASE("setting parameter values"){
    TestComponent tComp;
    std::vector<double> newParams(1, 5);
    std::vector<double>   listVals(10, 20);
    std::vector<double> vectorVals(10, 10);

    newParams.insert(newParams.end(), listVals.begin(), listVals.end());
    newParams.insert(newParams.end(), vectorVals.begin(), vectorVals.end());
                    
    tComp.SetParameterValues(newParams);
    REQUIRE(tComp.GetParameterValues() == newParams);
    REQUIRE(tComp.fDoubleParameter == 5);
    REQUIRE(tComp.fListParameters == std::list<double> (10, 20));
    REQUIRE(tComp.fVectorParameters == std::vector<double> (10, 10));

    // do it again - checks for state dependence
    tComp.SetParameterValues(newParams);
    REQUIRE(tComp.GetParameterValues() == newParams);
    REQUIRE(tComp.fDoubleParameter == 5);
    REQUIRE(tComp.fListParameters == std::list<double> (10, 20));
    REQUIRE(tComp.fVectorParameters == std::vector<double> (10, 10));

    
    
}

TEST_CASE("setting parameter names"){
    TestComponent tComp;
    tComp.ExposedSetParameterNames(std::vector<std::string>(21, "test"));
    REQUIRE(tComp.GetParameterNames() == std::vector<std::string>(21, "test"));
}
