/****************************************/
/* Abstract base class for an evaluator */
/****************************************/
#ifndef __EVALUATOR__
#define __EVALUATOR__
#include <vector>

class DataHandle;

class TestStatistic{
 public:
    TestStatistic(): fDataHandle(NULL) {}
    virtual ~TestStatistic() {}

    virtual double Evaluate() = 0;
    void SetParams(const std::vector<double>& params_); 
    // normalisations then systematics    
    size_t GetNParams() const {return fNpdfs + fNsystematics;}
    
    void    SetDataHandle(DataHandle* handle_);
    DataHandle* GetDataHandle() const;
    
 protected:
    DataHandle* fDataHandle;
    std::vector<double> fNormalisations;
    std::vector<double> fSystematicParams;
    size_t fNpdfs;
    size_t fNsystematics;
    
};
#endif
