#ifndef __OXSX_ANALYTIC_ED__
#define __OXSX_ANALYTIC_ED__
#include <EventDistribution.h>
#include <FitComponent.h>
#include <ObsSet.h>

class PDF;
class AnalyticED : public EventDistribution, public FitComponent{
 public:
    AnalyticED(PDF*); // make a copy
    AnalyticED(const AnalyticED& other_); // deep copy
    ~AnalyticED();         // frees fFunction
    EventDistribution* Clone() const;
    
    double Probability(const Event&) const;
    double Probability(const std::vector<double>&) const;

    double Integral() const;
    void   Normalise();

    void   SetObservables(const ObsSet&);
    ObsSet GetObservables() const;
    
    unsigned GetNDims() const;

    // FitComponent interface : pass on calls to fFunction, change names
    void MakeFittable();
    std::vector<std::string> GetParameterNames() const;
    std::vector<double>      GetParameters() const;
    double GetParameter(const std::string&) const;
    size_t GetParameterCount() const;

    void SetParameters(const std::vector<double>&);
    void SetParameterNames(const std::vector<std::string>&);
    void SetParameter(const std::string& name_, double val_);
    

 private:
    ObsSet        fObservables;
    PDF*          fFunction;
    double        fNorm;
};
#endif
