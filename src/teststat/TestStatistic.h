/****************************************/
/* Abstract base class for an evaluator */
/****************************************/
#ifndef __OXSX_TEST_STATISTIC__
#define __OXSX_TEST_STATISTIC__
#include <vector>
#include <stddef.h>
class DataSet;

class TestStatistic{
 public:
    TestStatistic(): fDataSet(NULL), fNpdfs(0), fNsystematics(0) {}
    virtual ~TestStatistic() {}

    virtual double Evaluate() = 0;
    void SetParams(const std::vector<double>& params_); 
    // normalisations then systematics    
    size_t GetNParams() const {return fNpdfs + fNsystematics;}
    
    void    SetDataSet(DataSet* handle_);
    DataSet* GetDataSet() const;
    
 protected:
    DataSet* fDataSet;
    std::vector<double> fNormalisations;
    std::vector<double> fSystematicParams;
    size_t fNpdfs;
    size_t fNsystematics;
    
};
#endif
