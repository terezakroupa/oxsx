/****************************************************/
/* Output of a fit routine, used for limit setting. */
/****************************************************/
#ifndef __OXSX_FIT_RESULT__
#define __OXSX_FIT_RESULT__
#include <Histogram.h>
#include <CutLog.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

typedef std::map<std::string, Histogram> HistMap;

class FitResult{
 public:
    FitResult() : fStatSpace(NULL), fIsValid(true), fSignalCutEfficiency(-1) {}
    FitResult(const FitResult&); //deep copy
    FitResult operator=(const FitResult&); //deep copy
    ~FitResult(); // frees stat space

    double GetSignalCutEfficiency() const;
    void   SetSignalCutEfficiency(double);

    CutLog GetSignalCutLog() const;
    void   SetSignalCutLog(const CutLog&);

    void  SetBestFit(const std::vector<double>&);
    std::vector<double> GetBestFit() const;

    std::vector<std::string> GetParameterNames() const;
    void SetParameterNames(const std::vector<std::string>&);

    void SetStatSpace(const Histogram&);
    const Histogram& GetStatSpace() const; 

    void SetStatSample(const std::vector<std::vector<double> >&);
    const std::vector<std::vector<double> >& GetStatSample() const;
    
    void SetValid(bool b_);
    bool GetValid() const;
    
    std::string AsString() const;
    void Print() const;
    void SaveAs(const std::string&) const;

    void Set1DProjections(const HistMap&);
    void Set2DProjections(const HistMap&);

    HistMap Get1DProjections() const;
    HistMap Get2DProjections() const;


 private:
    std::vector<double>               fBestFit;
    std::vector<std::string>          fParameterNames;
    std::vector<std::vector<double> > fStatSample;
    Histogram*    fStatSpace;
    HistMap f1DProjections;
    HistMap f2DProjections;
    
    double  fSignalCutEfficiency;
    CutLog  fSignalCutLog;

    bool fIsValid;
};
#endif

