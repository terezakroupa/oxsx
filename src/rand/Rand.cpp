#include <Rand.h>
#include <stdlib.h>
#include <TRandom3.h>

double
Rand::Uniform(double max_){
    return max_ * ((double) rand() / (RAND_MAX));
}

double 
Rand::Gaus(double mean_, double sigma_){
    TRandom3 rand3;
    rand3.SetSeed();
    return rand3.Gaus(mean_, sigma_);
}
