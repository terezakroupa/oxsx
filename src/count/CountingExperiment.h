#ifndef __OXSX_COUNTING_EXPERIMENT__
#define __OXSX_COUNTING_EXPERIMENT__
#include <CutCollection.h>
#include <EventSystematicManager.h>

class DataSet;
class EventSystematic;
class CountingExperiment{
 public:
    CountingExperiment() : fBackgroundCount(-1), fDataCount(-1) {}
    void   CountData(DataSet*);
    void   CountBackgrounds();

    double GetBackgroundCount() const;
    int    GetDataCount() const;

    void AddCut(const Cut&);
    void AddSystematic(EventSystematic*);
    void AddBackground(DataSet* mcData_, double rate_);    

 private:
    CutCollection          fCuts;
    EventSystematicManager fSystematics;
    std::vector<double>    fBackgroundNorms;
    std::vector<DataSet*>  fBackgroundDataSets;
    DataSet*               fTestDataSet;

    double fBackgroundCount;
    int    fDataCount;
};
#endif
