#include <catch.hpp>
#include <ParameterSampler.h>
#include <PDF.h>

class FakePDF{
public:
    FakePDF(int dim, double val) : fDim(dim), fVal(val) {}
    double Integral(const std::vector<double>& mins_,
                    const std::vector<double>& maxs_) const { return 1;}
    std::vector<double> Sample() const {return std::vector<double>(fDim, fVal);}

private:
    double fVal;
    int fDim;
};

TEST_CASE("2d Gaussian", ""){
    
}
