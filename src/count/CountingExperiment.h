#ifndef __OXSX_COUNTING_EXPERIMENT__
#define __OXSX_COUNTING_EXPERIMENT__
#include <CutCollection.h>
#include <EventSystematicManager.h>
#include <CountingResult.h>
#include <ParameterSampler.h>
#include <ComponentManager.h>
#include <string>

class PDF;
class DataSet;
class EventSystematic;
class Histogram;
typedef std::map<std::string, double> ParamMap;
class CountingExperiment{
 public:
    void CountData(DataSet*);
    void CountBackgrounds();
    void CountSignal();

    void AddCut(const Cut&, const std::string& name_);
    void AddBackground(DataSet* mcData_, double rate_, const std::string& name_);
    void SetSignal(DataSet* mcData_, const std::string& name_);

    void AddSystematic(EventSystematic*);
    void AddConstraint(PDF*, const std::string& paramName_);
    void AddConstraint(PDF*, const std::vector<std::string>& paramNames_);
    void SetSystematicParams(const ParamMap&);

    void CountAndSampleSystematics(int nrep_, Histogram& toFill_);
    const CountingResult& GetCountingResult() const;

 private:
    CutCollection            fCuts;
    std::vector<DataSet*>    fBackgroundDataSets;
    std::vector<double>      fBackgroundNorms;
    DataSet*                 fTestDataSet;
    DataSet*                 fSignalDataSet;

    EventSystematicManager   fSystematics;
    ParameterSampler         fSampler;
    ComponentManager         fCompManager;

    std::vector<std::string> fBackgroundNames;
    std::string              fSignalName;
    CountingResult           fResult;
    
    //internal, used by SampleSystematics & Countbackgrounds
    double CountIteration(bool saveToResult_);
};
#endif
