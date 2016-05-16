/*************************************************/
/* Wrap an evaluation routine for minuit to call */
/*************************************************/
#ifndef __MINUIT_FCN__
#define __MINUIT_FCN__
#include <TestStatistic.h>
#include <Minuit2/FCNBase.h>

class MinuitFCN : public ROOT::Minuit2::FCNBase{
 public:
    MinuitFCN() :fTestStatistic(NULL), fUp(0.5), fFlipSign(false) {}
    MinuitFCN(TestStatistic* statistic_) : fTestStatistic(statistic_), 
                                           fUp(0.5), fFlipSign(false){}

    //these two required by minit
    double Up() const {return fUp;} 
    double operator()(const std::vector<double>& params_) const {
        if(!fTestStatistic)
            throw 0;

        fTestStatistic->SetParameters(params_);
        if(fFlipSign)
            return -1 * fTestStatistic->Evaluate();

        return fTestStatistic -> Evaluate();
    }


    void   SetUp(double up_) {fUp = up_;}
    double GetUp() const {return Up();}

    void SetSignFlip(bool b_) {fFlipSign = b_;}
    bool GetSignFlip() const {return fFlipSign;}

 private:
    TestStatistic* fTestStatistic;
    double fUp;
    bool   fFlipSign;  // if true, result is multiplied by -ve 1. changes minimisation to maximisation
};
#endif
