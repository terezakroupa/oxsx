/****************************************************************************/
/* Test Statistics must implement the Evaluate method for optimisation,     */
/* as well as registering any components that should be adjusted in the fit */
/*     using AddFitComponent() in the method RegisterFitComponents()        */
/****************************************************************************/
#ifndef __OXSX_TEST_STATISTIC__
#define __OXSX_TEST_STATISTIC__
#include <ComponentManager.h>
#include <vector>
#include <stddef.h>

class DataSet;
class FitComponent;
class TestStatistic{
 public:
    TestStatistic(): fDataSet(NULL) {}
    virtual ~TestStatistic() {}

    virtual double Evaluate() = 0;    
    void   SetParameters(const std::vector<double>& params_);    
    int    GetParameterCount() const;
    
    virtual void    SetDataSet(DataSet* handle_);
    virtual DataSet* GetDataSet() const;

    // Set up all the components for a fit
    virtual void RegisterFitComponents() = 0;

 protected:
    DataSet* fDataSet;
    void     AddFitComponent(FitComponent*);

 private:
    ComponentManager fComponentManager;
};
#endif
