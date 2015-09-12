#include <FitRoutine.h>
#include <Evaluator.h>
#include <Optimiser.h>
#include <Handle.h>

FitRoutine::~FitRoutine(){
    delete fEvaluator;
    delete fOptimiser;
    delete fHandle;
}


void
FitRoutine::SetOptimiser(Optimiser* optimiser_){
    fOptimiser = optimiser_;
}

void 
FitRoutine::SetEvaluator(Evaluator* evaluator_){
    fEvaluator = evaluator_;
}

void 
FitRoutine::SetHandle(Handle* handle_){
    fHandle = handle_;
}

void
FitRoutine::Fit(){
    // loop untill the optimiser converges:
    
        // Set the rates 

       // apply the systematics

       // evaluate the statistic
    


}
