#ifndef __OXSX_MCMCSAMPLES__
#define __OXSX_MCMCSAMPLES__
#include <AxisCollection.h>
#include <Histogram.h>
#include <ParameterDict.h>

class MCMC;
class MCMCSamples{
 public:
    MCMCSamples(MCMC* p_) : fSaveFullHistogram(false), fAcceptedSteps(0), fTotalSteps(0),
                            fBurnIn(1000), fThinFactor(1), fInitialised(false), fMCMC(p_) {}


    int  GetBurnIn() const;
    void SetBurnIn(int);

    int  GetThinFactor() const;
    void SetThinFactor(int);
    
    void SetHistogramAxes(const AxisCollection&);
    AxisCollection GetHistogramAxes() const;

    bool GetSaveFullHistogram() const;
    void SetSaveFullHistogram(bool);

    double   GetRejectionRate() const;
    double   GetAcceptanceRate() const;

    void Fill(const ParameterDict&, bool accepted_);

    const std::vector<Histogram>& Get1DProjections() const;
    const std::vector<Histogram>& Get2DProjections() const;

    const Histogram& GetHistogram() const;
    const std::vector< std::vector<double> >& GetRawSamples() const;

    void Clear();
    
 private:
    MCMC*   fMCMC;
    bool    fInitialised;
    int     fBurnIn;
    int     fThinFactor;
    void    InitialiseHistograms();
    void    FillProjections(const ParameterDict&);
    
    // results
    bool      fSaveFullHistogram;
    AxisCollection fHistogramAxes;

    int fAcceptedSteps;
    int fTotalSteps;

    std::vector<Histogram>           f1DProjections;
    std::vector<Histogram>           f2DProjections;

    Histogram fHist;
    std::vector< std::vector<double> > fSample;

};

#endif
