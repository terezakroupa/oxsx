#include <catch.hpp>
#include <DenseMatrix.h>

TEST_CASE("Create a simple matrix"){
    DenseMatrix mat(3, 4);
    REQUIRE(mat.GetNRows() == 3);
    REQUIRE(mat.GetNCols() == 4);

    SECTION("Set zeros and access elements"){
        mat.SetZeros();
        double sum = 0;
        for(int i = 0; i < mat.GetNRows(); i++)
            for(int j = 0; j < mat.GetNCols(); j++)
                sum += mat(i, j);

        REQUIRE(sum == 0);
    }

    SECTION("setting elements"){
        mat(0, 0) = 1;
        REQUIRE(mat(0, 0) == 1);
    }
}

TEST_CASE("Matrix Multiplication"){
    DenseMatrix mat(2, 2);
    mat.SetZeros();
    mat(1, 0) = 1;
    mat(0, 1) = 1;
    
    DenseMatrix square = mat.Inner(mat);
    REQUIRE(square(1, 0) == 0);
    REQUIRE(square(0, 1) == 0);    
    REQUIRE(square(1, 1) == 1);
    REQUIRE(square(0, 0) == 1);
}

TEST_CASE("Determinant and inverse"){
    DenseMatrix mat(2, 2);
    mat(1, 0) = 2;
    mat(0, 1) = 1;
    mat(1, 1) = 3;
    mat(0, 0) = 4;

    SECTION("Inverse"){
        DenseMatrix inverse = mat.Inverse();
        REQUIRE(inverse(0, 0) == 0.3);
        REQUIRE(inverse(1, 1) == 0.4);
        REQUIRE(inverse(0, 1) == -0.1);
        REQUIRE(inverse(1, 0) == -0.2);
    }
    SECTION("det"){
        REQUIRE(mat.Det() == 10);
    }

}
