#ifndef __OXSX__HAMILTONIAN_SAMPLER__
#define __OXSX__HAMILTONIAN_SAMPLER__
#include <ParameterDict.h>
#include <MCSampler.h>
#include <Gradient.h>
#include <vector>

template<typename StatType>
class HamiltonianSampler : public MCSampler{
public:
    HamiltonianSampler(StatType& stat_, double epsilon_, int nSteps_);
    
    ParameterDict Draw(const ParameterDict& thisStep_);
    
    void SetMasses(const ParameterDict& m_) {fMasses = m_;}
    ParameterDict GetMasses() const {return fMasses;}
private:
    typedef Gradient<StatType> GradType;
    ParameterDict fMasses;
    int           fNSteps;
    GradType      fDiff;
    double        fEpsilon;
};
#include <HamiltonianSampler.hpp>
#endif
