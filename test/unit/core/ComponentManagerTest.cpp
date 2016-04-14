#include <catch.hpp>
#include <ComponentManager.h>
#include <DoubleParameter.h>
#include <ContainerParameter.h>
#include "TestComponent.h"

TEST_CASE("Stand alone component manager"){
    ComponentManager cmpMan;

    TestComponent testComp;
    TestComponent testComp2;

    SECTION("initialised correctly"){
        REQUIRE(cmpMan.GetTotalParameterCount() == 0);
        REQUIRE(cmpMan.GetParameters() == std::vector<double>(0));
        REQUIRE(cmpMan.GetParameterNames() == std::vector<std::string> (0));
    }
    
    SECTION("adding a component"){
        cmpMan.AddComponent(&testComp);
        REQUIRE(cmpMan.GetTotalParameterCount() == 21);
    }

    SECTION("adding two"){
        cmpMan.AddComponent(&testComp);
        cmpMan.AddComponent(&testComp2);
        REQUIRE(cmpMan.GetTotalParameterCount() == 21 * 2);
        
        cmpMan.SetParameters(std::vector<double> (21 * 2, 8));
        REQUIRE(testComp.GetParameterValues() == std::vector<double>(21, 8));
        REQUIRE(testComp2.GetParameterValues() == std::vector<double>(21, 8));
    }
    SECTION("clearing"){
        cmpMan.Clear();
        REQUIRE(cmpMan.GetParameters() == std::vector<double>(0));    
        REQUIRE(cmpMan.GetTotalParameterCount() == 0);
        REQUIRE(cmpMan.GetParameterNames() == std::vector<std::string>(0));
    }
    
}
