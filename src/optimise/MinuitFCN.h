/*************************************************/
/* Wrap an evaluation routine for minuit to call */
/*************************************************/
#ifndef __MINUIT_FCN__
#define __MINUIT_FCN__
#include <TestStatistic.h>
#include <Minuit2/FCNBase.h>

class MinuitFCN : public ROOT::Minuit2::FCNBase{
 public:
    MinuitFCN(TestStatistic* statistic_) : fTestStatistic(statistic_), fUp(0.5){}

    //these two required by minit
    double Up() const {return fUp;} 
    double operator()(const std::vector<double>& params_) const {
        fTestStatistic->SetParams(params_);
        return fTestStatistic->Evaluate();
    }


    void   SetUp(double up_) {fUp = up_;}
    double GetUp() const {return Up();}

 private:
    TestStatistic* fTestStatistic;
    double fUp;
};
#endif
