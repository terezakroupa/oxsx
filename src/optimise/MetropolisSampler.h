#ifndef __OXSX_METROPOLIS_SAMPLER__
#define __OXSX_METROPOLIS_SAMPLER__
#include <MCSampler.h>
#include <ParameterDict.h>

class MetropolisSampler : public MCSampler{
 public:
    const ParameterDict& GetSigmas() const;
    void  SetSigmas(const ParameterDict&);

    ParameterDict Draw(const ParameterDict& current_);

 private:
    ParameterDict fSigmas;
};
#endif
