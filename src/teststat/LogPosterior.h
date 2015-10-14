/******************************************************************************************************/
/* A Bayesian posterior made up of another testspace and a prior. This can only really make sense if  */
/* the underlying test space is a LH or chisquare.                                                    */
/* Currently assumes that the test stat is a NLLH likelihood, straightforward to change later         */
/* NOTE: mapping out the posterior with this class does not produce a normalised space - we don't     */
/* know the shape yet - must be normalised before any integration                                     */
/******************************************************************************************************/

#ifndef __OXSX_POSTERIOR__
#define __OXSX_POSTERIOR__
#include <TestStatistic.h>

class Function;
class LogPosterior : public TestStatistic{
 public:
    LogPosterior(TestStatistic*, Function*);
    ~LogPosterior(){}

    void SetTestStat(TestStatistic*);
    TestStatistic* GetTestStat() const;

    void SetPrior(Function*);
    Function* GetPrior() const;

    virtual double Evaluate();
    virtual void SetDataSet(DataSet* dataSet_);
    virtual DataSet* GetDataSet() const;

    virtual void SetParams(const std::vector<double>& params_);
    virtual size_t GetNParams()  const;
    
 private:
    TestStatistic* fTestStat;
    Function* fPrior; 
    std::vector<double> fParams;
};
#endif
