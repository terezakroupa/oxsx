#ifndef __MINUIT__
#define __MINUIT__
#include <TMinuit.h>
class Minuit : Optimiser{
 public:
    Minuit();
    ~Minuit();
    
 private:
    TMinuit fMinuit;
    
};
#endif
