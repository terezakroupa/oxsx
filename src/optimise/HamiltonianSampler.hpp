#include <Rand.h>
#include <ContainerTools.hpp>
#include <LeapFrog.h>
#include <iostream>
#include <cmath>

template<typename StatType>
HamiltonianSampler<StatType>::HamiltonianSampler(StatType& stat_, double epsilon_, int nSteps_)
    : fEpsilon(epsilon_), fNSteps(nSteps_), fDiff(GradType(stat_, 0.05 * epsilon_)){

    typedef std::set<std::string> StringSet;
    StringSet names = stat_.GetParameterNames();
    for(StringSet::iterator it = names.begin(); it != names.end(); ++it)
        fMasses[*it] = 1;
}


template<typename StatType>
ParameterDict
HamiltonianSampler<StatType>::Draw(const ParameterDict& thisStep_){
    // step 1: sample from masses to create momenta
    ParameterDict momenta;
    
    for(ParameterDict::const_iterator it = thisStep_.begin(); it != thisStep_.end(); ++it){
        momenta[it->first] = Rand::Gaus(0, sqrt(fMasses[it->first]));
    }

    // step 2: Hamiltonian dynamics
    ParameterDict nextStep = thisStep_;
    for(int i  = 0; i < fNSteps; i++){
        LeapFrog::Hamiltonian(nextStep, momenta, fMasses, fEpsilon, fDiff);
        

        // look for reflections
        for(ParameterDict::iterator it = fMinima.begin(); it != fMinima.end();
            ++it){
            if (nextStep.at(it->first) < it->second)
                momenta[it->first] *= -1;
        }
        
        for(ParameterDict::iterator it = fMaxima.begin(); it != fMaxima.end();
            ++it){
            if (nextStep.at(it->first) > it->second)
                momenta[it->first] *= -1;
        }
            

    }

    return nextStep;
}

template<typename StatType>
void
HamiltonianSampler<StatType>::SetMinima(const ParameterDict& m_){
    fMinima = m_;
}

template<typename StatType>
ParameterDict
HamiltonianSampler<StatType>::GetMinima() const{
    return fMinima;
}

template<typename StatType>
void
HamiltonianSampler<StatType>::SetMaxima(const ParameterDict& m_){
    fMaxima = m_;
}

template<typename StatType>
ParameterDict
HamiltonianSampler<StatType>::GetMaxima() const{
    return fMaxima;
}
