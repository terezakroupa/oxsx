#include <NLLH.h>
#include <math.h>
#include <Handle.h>
double 
NLLH::Evaluate(){
    // Adjust Systematics
    fSystematicManager.SetParameters(fSystematicParams);
    
    // Apply systematics
    fPdfManager.ApplySystematics(fSystematicManager.GetSystematics());

    // Set Normalisations
    fPdfManager.SetNormalisations(fNormalisations);

    // loop over events and calculate P(data | {N, #delta})
    double nLogLH = 0;
    for(size_t i = 0; i < fHandle -> GetNEntries(); i++){
        DataHandler eventData = fHandle->GetEntry(i);
        nLogLH -= fPdfManager.Probability(eventData);
    }

    // Extended LH correction
    for(size_t i = 0; i < fNormalisations.size(); i++)
        nLogLH += fNormalisations.at(i);

    // Constraints
    
    
    return nLogLH;
}
