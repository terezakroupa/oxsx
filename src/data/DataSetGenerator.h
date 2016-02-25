/******************************************************************************************/
/* Generate mixed data samples from a set of other data samples.                          */
/* Either take the expected number or a poisson fluctuation around the underlying rate    */
/* WARNING: The generator only owns pointers to the other data sets to avoid large copies */
/******************************************************************************************/

#ifndef __OXSX_DATA_SET_GENERATOR__
#define __OXSX_DATA_SET_GENERATOR__
#include <cstdlib>
#include <vector>
#include <CutCollection.h>

class OXSXDataSet;
class DataSet;
class EventData;

class DataSetGenerator{
 public:
    DataSetGenerator() : fBootstrap(false){}
    ~DataSetGenerator() {}
    void SetDataSets(const std::vector<DataSet*> sets_);
    void SetExpectedRates(const std::vector<double>& rates_);
    void AddDataSet(DataSet* data_, double rates_);
    
    void SetCuts(const CutCollection& cuts_);
    void AddCut(const Cut& cut_);

    bool GetBootstrap() const;
    void SetBootstrap(bool);

    OXSXDataSet ExpectedRatesDataSet();
    OXSXDataSet PoissonFluctuatedDataSet(); 
    OXSXDataSet AllValidEvents();
    
    void Reset();
    void ClearDataSets();

 private:
    std::vector<DataSet*>    fDataSets;
    std::vector<double>      fExpectedRates;

    std::vector<std::vector<size_t> > fSelectedEvents;
    CutCollection            fCuts;
    EventData                RandomEvent(size_t handleIndex_);
    bool                     fBootstrap;
};

#endif
