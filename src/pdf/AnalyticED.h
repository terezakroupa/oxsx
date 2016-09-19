#ifndef __OXSX_ANALYTIC_ED__
#define __OXSX_ANALYTIC_ED__
#include <EventDistribution.h>
#include <FitComponent.h>
#include <DataRepresentation.h>

class PDF;
class AnalyticED : public EventDistribution, public FitComponent{
 public:
    AnalyticED(PDF*); // make a copy
    AnalyticED(const AnalyticED& other_); // deep copy
    ~AnalyticED();         // frees fFunction
    EventDistribution* Clone() const;
    
    double Probability(const EventData&) const;
    double Probability(const std::vector<double>&) const;

    double Integral() const;
    void   Normalise();

    void SetDataRep(const DataRepresentation&);
    DataRepresentation GetDataRep() const;
    
    unsigned GetNDims() const;

    // FitComponent interface : pass on calls to fFunction, change names
    void MakeFittable();
    std::vector<std::string> GetParameterNames() const;
    std::vector<double>      GetParameters() const;
    size_t                   GetParameterCount() const;
    void SetParameters(const std::vector<double>&);
    

 private:
    DataRepresentation  fDataRep;
    PDF*                fFunction;
    double              fNorm;
};
#endif
