/****************************************/
/* Abstract base class for an evaluator */
/****************************************/
#ifndef __EVALUATOR__
#define __EVALUATOR__
#include <vector>
#include <stddef.h>
class DataSet;

class TestStatistic{
 public:
    TestStatistic(): fDataSet(NULL), fNpdfs(0), fNsystematics(0) {}
    virtual ~TestStatistic() {}

    virtual double Evaluate() = 0;
    virtual void SetParams(const std::vector<double>& params_); 
    // normalisations then systematics    
    virtual size_t GetNParams() const {return fNpdfs + fNsystematics;}
    
    virtual void    SetDataSet(DataSet* handle_);
    virtual DataSet* GetDataSet() const;

    size_t GetNpdfs () const;
    size_t GetNsystematics () const;
    
 protected:
    DataSet* fDataSet;
    std::vector<double> fNormalisations;
    std::vector<double> fSystematicParams;
    size_t fNpdfs;
    size_t fNsystematics;
    
};
#endif
