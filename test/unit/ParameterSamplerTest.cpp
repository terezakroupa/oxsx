#include <catch.hpp>
#include <ParameterSampler.h>
#include <PDF.h>

class FakePDF : public PDF{
public:
    FakePDF(int dim, double val) : fDim(dim), fVal(val) {}
    double Integral(const std::vector<double>& mins_,
                    const std::vector<double>& maxs_) const { return 1;}

    std::vector<double> Sample() const {return std::vector<double>(fDim, fVal);}
    Function* Clone() const {return new FakePDF(*this);}
    int GetNDims() const {return fDim;}
    
    double operator()(const std::vector<double>&) const {return 1;}

    std::vector<std::string> GetParameterNames() const {return std::vector<std::string>();}
    void SetParameter(const std::string&, double val) {}
    double GetParameter(const std::string&) const {return 1;}
    void SetParameterNames(const std::vector<std::string>&) {}
    void SetParameters(const std::vector<double>&) {}

    std::vector<double> GetParameters() const {return std::vector<double>();}
    size_t GetParameterCount() const {return fDim;}

    void MakeFittable() {}
private:
    double fVal;
    int fDim;
};


TEST_CASE("Sampling", ""){
    ParameterSampler samp;
    FakePDF fp1(1, 1);
    FakePDF fp2(2, 2);
    samp.AddParameter(&fp1, "1");

    SECTION("1D"){
        std::map<std::string, double> sample = samp.Sample();
        REQUIRE(sample.size() == 1);
        REQUIRE(sample["1"] == 1);
    }
    
    SECTION("2D+1D"){
        std::vector<std::string> correlatedSet;
        correlatedSet.push_back("2");
        correlatedSet.push_back("3");
        
        samp.AddCorrelatedSet(&fp2, correlatedSet);
        std::map<std::string, double> sample = samp.Sample();
        sample = samp.Sample();
        sample = samp.Sample();
        sample = samp.Sample();

        REQUIRE(sample.size() == 3);
        REQUIRE(sample["1"] == 1);
        REQUIRE(sample["2"] == 2);
        REQUIRE(sample["3"] == 2);
    }
}
