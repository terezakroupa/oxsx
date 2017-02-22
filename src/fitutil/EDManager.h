#ifndef __OXSX_ED_MANAGER__
#define __OXSX_ED_MANAGER__
#include <FitComponent.h>
#include <ParameterManager.h>
#include <vector>

class EventDistribution;
class Event;

class EDManager : public FitComponent{
 public:
    EDManager(): fNDists(0), fNDims(0) {}
    ~EDManager(); // free pdf copies

    void  AddDist(EventDistribution*); // take a copy
    void  AddDists(const std::vector<EventDistribution*>& pdfs_);

    const std::vector<double>& GetNormalisations() const;
    void  SetNormalisations(const std::vector<double>&);
    
    double Probability(const Event&) const;
    
    size_t GetNDists() const;
    size_t GetNDims() const;
    
    // Make a fittable component - i.e. rescale pdfs inside to fit
    void  MakeFittable();    
    std::vector<std::string> GetParameterNames() const;
    std::vector<double> GetParameters() const;
    size_t GetParameterCount() const;
    void   SetParameters(const std::vector<double>& params_);

 private:
    ParameterManager       fParameterManager;
    size_t fNDists;
    size_t fNDims;
    std::vector<EventDistribution*>   fDists;
    std::vector<double> fNormalisations;
};
#endif
