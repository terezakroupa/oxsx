#include <Rand.h>
#include <ContainerTools.hpp>
#include <LeapFrog.h>
#include <iostream>

template<typename StatType>
HamiltonianSampler<StatType>::HamiltonianSampler(StatType& stat_, double epsilon_, int nSteps_)
    : fEpsilon(epsilon_), fNSteps(nSteps_), fDiff(GradType(stat_, epsilon_/100)){}


template<typename StatType>
ParameterDict
HamiltonianSampler<StatType>::Draw(const ParameterDict& thisStep_){
    // step 1: sample from masses to create momenta
    ParameterDict momenta;
    
    for(ParameterDict::const_iterator it = thisStep_.begin(); it != thisStep_.end(); ++it){
        fMasses[it->first] = 1;
        momenta[it->first] = Rand::Gaus(0, fMasses[it->first]);
    }

    // step 2: Hamiltonian dynamics
    ParameterDict nextStep = thisStep_;
    for(int i  = 0; i < fNSteps; i++)
        LeapFrog::Hamiltonian(nextStep, momenta, fMasses, fEpsilon, fDiff);


    return nextStep;
}


