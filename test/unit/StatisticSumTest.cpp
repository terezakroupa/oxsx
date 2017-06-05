#include <catch.hpp>
#include <StatisticSum.h>

class FakeStatistic : public TestStatistic{
public:
    double Evaluate() {
        return fVal;
    }

    int GetParameterCount() const {
        return 1;
    }

    void SetParameters(const ParameterDict& p){
        fVal = p.at(fParamName);
    }

    ParameterDict GetParameters() const{
        ParameterDict p; 
        p[fParamName] = fVal;
        return p;
    } 

    std::vector<std::string> GetParameterNames() const{
        return std::vector<std::string>(1, fParamName);
    }

    void RegisterFitComponents() {}

    double fVal;
    std::string fParamName;
};

TEST_CASE("Adding test statistics using StatisticSum constr"){
    FakeStatistic s1;
    FakeStatistic s2;
    
    s1.fVal = 1;
    s1.fParamName = "p1";
    s2.fVal = 2;
    s2.fParamName = "p2";

    SECTION("no shared parameters"){
        StatisticSum sum(s1, s2);
        REQUIRE(sum.GetParameterCount() == 2);
        std::vector<std::string> expectedNames;
        expectedNames.push_back("p1");
        expectedNames.push_back("p2");

        ParameterDict expectedVals;
        expectedVals["p1"] = 1;
        expectedVals["p2"] = 2;

        REQUIRE(sum.GetParameters() == expectedVals);
        REQUIRE(sum.GetParameterNames() == expectedNames);

        REQUIRE(sum.Evaluate() == 3); // 2 + 1
    
        ParameterDict setVals;
        setVals["p1"] = 3;
        setVals["p2"] = 4;

        sum.SetParameters(setVals);
        REQUIRE(s1.fVal == 3);
        REQUIRE(s2.fVal == 4);
        
        REQUIRE(sum.Evaluate() == 7); // 3 + 4
    }
    
    SECTION("setting with shared parameters"){
        StatisticSum sum(s1, s2);
        s1.fParamName = "p2";

        REQUIRE(sum.GetParameterNames() == std::vector<std::string>(1, "p2"));        
        REQUIRE(sum.GetParameterCount() == 1);


        ParameterDict p;
        p["p1"] = 10;
        REQUIRE(sum.Evaluate() == 20); // 10 + 10
        
    }
}
