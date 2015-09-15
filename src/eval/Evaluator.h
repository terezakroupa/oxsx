/****************************************/
/* Abstract base class for an evaluator */
/****************************************/
#ifndef __EVALUATOR__
#define __EVALUATOR__
#include <vector>

class Handle;

class Evaluator{
 public:
    Evaluator(): fHandle(NULL) {}
    virtual ~Evaluator() {}

    virtual double Evaluate() = 0;
    void SetParams(const std::vector<double>& params_); 
    // normalisations then systematics    
    size_t GetNParams() const {return fNpdfs + fNsystematics;}
    
    void SetDataHandle(Handle* handle_);
    Handle* GetDataHandle() const;
    
 protected:
    Handle* fHandle;
    std::vector<double> fNormalisations;
    std::vector<double> fSystematicParams;
    size_t fNpdfs;
    size_t fNsystematics;
    
};
#endif
