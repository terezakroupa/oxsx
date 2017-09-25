#ifndef __OXSX__LEAP_FROG__
#define __OXSX__LEAP_FROG__
#include <vector>
#include <ParameterDict.h>

class LeapFrog{
public:
    template<typename T>
    static void Hamiltonian(ParameterDict& qs_, ParameterDict& ps_,
                            const ParameterDict& masses_,
                            double epsilon_, T&);
};

#include <LeapFrog.hpp>
#endif
