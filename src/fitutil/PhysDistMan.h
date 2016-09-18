#ifndef __OXSX_PHYSDISTMAN__
#define __OXSX_PHYSDISTMAN__
#include <FitComponent.h>
#include <ParameterManager.h>
#include <vector>

class PhysDist;
class EventData;

class PhysDistMan : public FitComponent{
 public:
    PhysDistMan(): fNDists(0), fNDims(0) {}
    ~PhysDistMan(); // free pdf copies

    void  AddPhysDist(PhysDist*); // take a copy
    void  AddPhysDists(const std::vector<PhysDist*>& pdfs_);

    const std::vector<double>& GetNormalisations() const;
    void  SetNormalisations(const std::vector<double>&);
    
    double Probability(const EventData&) const;
    
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
    std::vector<PhysDist*>   fDists;
    std::vector<double> fNormalisations;
};
#endif
