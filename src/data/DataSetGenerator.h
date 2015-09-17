/**************************************************/
/* Generate fake data set from a large MC samples */
/**************************************************/
#ifndef __DATA_SET_GENERATOR__
#define __DATA_SET_GENERATOR__
#include <vector>

class DataHandle;
class DataSet;
class EventData;

class DataSetGenerator{
 public:
    DataSetGenerator() {}
    ~DataSetGenerator() {}
    void SetDataHandles(const std::vector<DataHandle*> handles_);
    void SetExpectedRates(const std::vector<double>& rates_);
    
    DataSet ExpectedRatesDataSet() const;
    DataSet PoissonFluctuatedDataset() const;

 private:
    std::vector<DataHandle*> fDataHandles;
    std::vector<double>      fExpectedRates;
    EventData                RandomEvent(size_t handleIndex_) const;
};

#endif
