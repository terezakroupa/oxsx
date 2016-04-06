#include <catch.hpp>
#include <Vector.h>

TEST_CASE("Test Constructors"){
    SECTION("Empty"){
        Vector v;
        REQUIRE(v.GetNDims() == 0);
    }

    SECTION("Uninitialised list"){
        Vector v(5);
        REQUIRE(v.GetNDims() == 5);
    }

    SECTION("Initialised to same val"){
        Vector v(5, 5);
        double sum = 0;
        for(int i = 0; i < v.GetNDims(); i++)
            sum += v(i);
        REQUIRE(sum == 5 * 5);
    }
    
    SECTION("Initialised from stl vector"){
        std::vector<double> stl;
        stl.push_back(0);
        stl.push_back(1);
        stl.push_back(2);
        stl.push_back(3);
        Vector v(stl);
        REQUIRE(v.GetNDims() == 4);
        REQUIRE(v(0) == 0);
        
        double sum = 0;
        for(int i = 0; i < v.GetNDims(); i++)
            sum += v(i);
        REQUIRE(sum == 6);
    }
}

TEST_CASE("stl conversion"){
    std::vector<double> v;
    for(int i = 0; i < 10; i++)
        v.push_back(i);

    for(int i = 10; i > 0; i--)
        v.push_back(i);

    REQUIRE(Vector(v).AsSTL() == v);
}

TEST_CASE("Other operations"){
    std::vector<double> v;
    v.push_back(3);
    v.push_back(4);
    Vector testVec(v);

    SECTION("Norm"){
        REQUIRE(testVec.Norm() == 5 );
    }
    
    SECTION("clear"){
        testVec.Clear();
        REQUIRE(testVec.GetNDims() == 0);
        REQUIRE(testVec.Norm() == 0);
    }
    
}
TEST_CASE("Set all values at once"){
    Vector v(10);
    SECTION("zeros"){
        v.Zeros();
        REQUIRE(0 == v.Norm());
    }

    SECTION("ones"){
        v.Fill(1);
        REQUIRE(Approx(3.16227766) == v.Norm());
    }
}

TEST_CASE("Dot product"){
    Vector  v(5, 3);
    Vector v2(5, 2);

    REQUIRE(v.Inner(v2) == 5 * 3 * 2);
}
