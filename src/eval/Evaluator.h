/****************************************/
/* Abstract base class for an evaluator */
/****************************************/
#ifndef __EVALUATOR__
#define __EVALUATOR__
#include <vector>

class PdfCollection;
class Handle;

class Evaluator{
 public:
    Evaluator(): fHandle(NULL) {}
    virtual ~Evaluator();
    virtual double Evaluate(const PdfCollection&) = 0;

 private:
    Handle* fHandle;
};
#endif
