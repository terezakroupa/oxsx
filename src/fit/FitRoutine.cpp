#include <FitRoutine.h>
#include <Evaluator.h>
#include <Optimiser.h>
#include <Handle.h>
#include <FitResult.h>
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

FitResult
FitRoutine::Fit(){
    // loop untill the optimiser converges:
    while(fOptimiser->Iterate()){
        // interpret parameters
        SplitParams(fOptimiser->GetParams());
        
        // Set Normalisations
        fPdfs.SetNormalisations(fNormalisationParams);

        // Adjust Systematics
        fSystematicManager.SetParameters(fSystematicParams);
        
        // Apply the Systematics
        fPdfs.ApplySystematics(fSystematicManager.GetSystematics());

        // Calculate the test statistic
        fOptimiser->SetTestValue(fEvaluator->Evaluate(fPdfs));
    }
    return FitResult();
}

void
FitRoutine::SplitParams(const std::vector<double>& params_){
    fNormalisationParams.insert(fNormalisationParams.begin(), 
                                params_.begin(), params_.begin() + fNPdfs);

    fSystematicParams.insert(fSystematicParams.begin(), params_.begin() + fNPdfs, params_.end());
}
