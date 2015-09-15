#include <NLLH.h>
#include <math.h>
#include <Handle.h>
double 
NLLH::Evaluate(){

    // Adjust Systematics
    fSystematicManager.SetParameters(fSystematicParams);
    
    // Apply systematics
    fPdfCollection.ApplySystematics(fSystematicManager.GetSystematics());

    // loop over events and calculate P(data | {N, #delta})
    double log_prob = 0;
    for(size_t i = 0; i < fHandle -> GetNEntries(); i++){
        DataHandler eventData = fHandle->GetEntry(i);
        log_prob -= fPdfCollection.Probability(eventData);
    }

    return log_prob;
}
