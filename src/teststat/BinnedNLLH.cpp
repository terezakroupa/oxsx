#include <BinnedNLLH.h>
#include <math.h>
#include <DataHandle.h>
double 
BinnedNLLH::Evaluate(){
    // Adjust Systematics
    fSystematicManager.SetParameters(fSystematicParams);
    
    // Apply systematics
    fPdfManager.ApplySystematics(fSystematicManager.GetSystematics());

    // Set Normalisations
    fPdfManager.SetNormalisations(fNormalisations);

    // loop over events and calculate P(data | {N, #delta})
    double nLogLH = 0;
    for(size_t i = 0; i < fDataHandle -> GetNEntries(); i++){
        EventData eventData = fDataHandle->GetEntry(i);
        nLogLH -= fPdfManager.Probability(eventData);
    }

    // Extended LH correction
    for(size_t i = 0; i < fNormalisations.size(); i++)
        nLogLH += fNormalisations.at(i);

    // Constraints
    
    
    return nLogLH;
}
