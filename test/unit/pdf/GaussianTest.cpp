#include <catch.hpp>
#include <Gaussian.h>
#include <iostream>

TEST_CASE("2D gaussian", "[Gaussian]"){
    std::vector<double> means;
    means.push_back(0);
    means.push_back(1);

    std::vector<double> stDevs;
    stDevs.push_back(2);
    stDevs.push_back(3);


    Gaussian gaus(means, stDevs);

    // set params right
    REQUIRE(gaus.GetMean(0) == 0);
    REQUIRE(gaus.GetMean(1) == 1);

    REQUIRE(gaus.GetStDev(0) == 2);
    REQUIRE(gaus.GetStDev(1) == 3);
    
    // organised right
    REQUIRE(gaus.GetParameters().size() == 4);
    REQUIRE(gaus.GetParameter(0) == 0);
    REQUIRE(gaus.GetParameter(1) == 2);
    REQUIRE(gaus.GetParameter(2) == 1);
    
}

TEST_CASE("1D gaussian", "[Gaussian]"){
    Gaussian gaus(0, 1);

    SECTION("Check paramter storage"){

        REQUIRE(gaus.GetMean(0) == 0);
        REQUIRE(gaus.GetStDev(0) == 1);
        
        REQUIRE(gaus.GetParameters().size() == 2);
        REQUIRE(gaus.GetParameters().at(1) == gaus.GetStDev(0));
    }

    SECTION("Check probability"){
        REQUIRE(gaus(std::vector<double>(1,1)) == Approx(0.24197));
        REQUIRE(gaus(std::vector<double> (1,1E8)) == Approx(0));
        REQUIRE(gaus(std::vector<double> (1,-1E8)) == Approx(0));
    }


    SECTION("Test CDF"){
        REQUIRE(gaus.Cdf(0, 1) == Approx(0.841344));
        REQUIRE(gaus.Cdf(0, 100) == Approx(1));
        REQUIRE(gaus.Cdf(0, -100) == Approx(0));
    }

    SECTION("Test Integral"){
        REQUIRE(gaus.Integral(-1,1) == Approx(0.6827));
        REQUIRE(gaus.Integral(-100,100) == Approx(1));
        REQUIRE(gaus.Integral(0,0) == Approx(0));
    }
}
