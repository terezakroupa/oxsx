#include <catch.hpp>
#include <list>
#include <ParameterManager.h>
#include <DoubleParameter.h>
#include <vector>
#include <iostream>

    
TEST_CASE("Do parameters register correctly?"){
    ParameterManager paramMan;
    std::vector<double> vecParams(10, 0);
    double doubleParam;
    std::list<double> listParams(10, 0);
    
    paramMan.Add(new DoubleParameter(doubleParam), "double");
    paramMan.AddContainer<std::list<double> >(listParams, "list");
    for(size_t i = 0; i < vecParams.size(); i++){
        std::stringstream ss;
        ss << "vector " << i;
        paramMan.Add(
                 new ContainerParameter<std::vector<double> >(vecParams,i), 
                 ss.str()
                     );
    }

    SECTION("Parameter values"){
        REQUIRE(paramMan.GetParameterCount() == 21);
        REQUIRE(paramMan.GetParameters() == std::vector<double>(21, 0));
    }
    SECTION("Parameter Names"){
        std::vector<std::string> expectedNames(1, "double");    
        for(size_t i = 0; i < listParams.size(); i++){
            std::stringstream ss;
            ss << "list " << i;
            expectedNames.push_back(ss.str());
        }

        for(size_t i = 0; i < vecParams.size(); i++){
            std::stringstream ss;
            ss << "vector " << i;
            expectedNames.push_back(ss.str());
        }
        REQUIRE(paramMan.GetParameterNames() == expectedNames);

    }

    SECTION("after copy"){
        ParameterManager paramManCopy(paramMan);
        REQUIRE(paramManCopy.GetParameterCount() == 0);
    }



    SECTION("setting parameter values"){        
        std::vector<double> newParams(1, 5);
        std::vector<double>   listVals(10, 20);
        std::vector<double> vectorVals(10, 10);

        newParams.insert(newParams.end(), listVals.begin(), listVals.end());
        newParams.insert(newParams.end(), vectorVals.begin(), vectorVals.end());
                    
        paramMan.SetParameters(newParams);
        REQUIRE(paramMan.GetParameters() == newParams);
        REQUIRE(doubleParam == 5);
        REQUIRE(listParams == std::list<double> (10, 20));
        REQUIRE(vecParams == std::vector<double> (10, 10));

        // do it again - checks for state dependence
        paramMan.SetParameters(newParams);
        REQUIRE(paramMan.GetParameters() == newParams);
        REQUIRE(doubleParam == 5);
        REQUIRE(listParams == std::list<double> (10, 20));
        REQUIRE(vecParams == std::vector<double> (10, 10));

    
    
    }

}
