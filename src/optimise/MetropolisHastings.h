#ifndef __OXSX_METROPOLIS_HASTINGS__
#define __OXSX_METROPOLIS_HASTINGS__
#include <Optimiser.h>
#include <FitResult.h>
#include <Histogram.h>

class TestStatistic;
class MetropolisHastings : public Optimiser{
 public:
     MetropolisHastings() : fBurnIn(3000), 
                            fMaxIter(100000), fThinFactor(1), 
                            fMaxVal(0), fFlipSign(false), 
                            fTestStatLogged(false), pTestStatistic(NULL),
                            fSaveFullHistogram(false)
                            {}               
    
    const FitResult& Optimise(TestStatistic*); 

    unsigned GetBurnIn() const;
    void     SetBurnIn(unsigned);
    
    unsigned GetThinFactor() const;
    void     SetThinFactor(unsigned);
    
    unsigned GetMaxIter() const;
    void     SetMaxIter(unsigned);

    double   GetRejectionRate() const;

    std::vector<double> GetMaxima() const;
    void SetMaxima(const std::vector<double>&);

    std::vector<double> GetMinima() const;
    void SetMinima(const std::vector<double>&);

    const std::vector<double>& GetSigmas() const;
    void   SetSigmas(const std::vector<double>&);

    bool GetFlipSign() const;
    void SetFlipSign(bool);
    
    bool GetTestStatLogged() const;
    void SetTestStatLogged(bool b_);

    bool GetSaveFullHistogram() const;
    void SetSaveFullHistogram(bool);
    void SetHistogramAxes(const AxisCollection&);
    AxisCollection GetHistogramAxes() const;

    void SetInitialTrial(const std::vector<double>&);
    std::vector<double> GetInitialTrial() const;

 private:
    // configuration
    unsigned  fBurnIn;
    unsigned  fThinFactor;
    unsigned  fMaxIter;
    unsigned  fNDims;
    bool      fTestStatLogged;
    bool      fFlipSign;
    bool      fSaveFullHistogram;
    AxisCollection fHistogramAxes;

    std::vector<double> fMaxima;
    std::vector<double> fMinima;
    std::vector<double> fSigmas;
    std::vector<double> fInitialTrial;

    // internal copy
    TestStatistic* pTestStatistic;

    // results
    double fRejectionRate;

    std::vector<Histogram>            f1DProjections;
    std::vector<std::vector<size_t> > f2DProjectionIndices;
    std::vector<Histogram>            f2DProjections;

    Histogram fHist;
    std::vector< std::vector<double> > fSample;

    FitResult fFitResult;
    std::vector<double> fBestFit;
    double fMaxVal;
    
    // private functions
    std::vector<double> JumpDraw(const std::vector<double>& thisStep_) const; 
    inline double JumpProbRatio(const std::vector<double>& thisStep_, 
                                const std::vector<double>& proposedStep_) const {return 1;}

    bool   StepAccepted(const std::vector<double>& thisStep_,
                        const std::vector<double>& proposedStep_);
    
    void    InitialiseHistograms();
    void    FillProjections(const std::vector<double>&);
	void    SaveProjections();
};
#endif

