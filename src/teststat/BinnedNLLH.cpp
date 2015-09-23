#include <BinnedNLLH.h>
#include <math.h>
#include <DataHandle.h>
#include <iostream>

double 
BinnedNLLH::Evaluate(){
    if (!fCalculatedDataPdf){
        BinData();
    }

    // Adjust Systematics
    fSystematicManager.SetParameters(fSystematicParams);

    // Apply systematics
    fPdfManager.ApplySystematics(fSystematicManager.GetSystematics());

    // Set Normalisations
    fPdfManager.SetNormalisations(fNormalisations);

    // loop over bins and calculate the likelihood
    double nLogLH = 0;
    for(size_t i = 0; i < fDataPdf.GetNBins(); i++){
        double prob = fPdfManager.Probability(EventData(fDataPdf.GetAxes().GetBinCentre(i)));
        nLogLH -= fDataPdf.GetBinContent(i) *  log(prob);
    }
    // Extended LH correction
    for(size_t i = 0; i < fNormalisations.size(); i++)
        nLogLH += fNormalisations.at(i);
            
    // Constraints    
    
    return nLogLH;
}

void
BinnedNLLH::BinData(){
    BinnedPdf dataPdf(fPdfManager.GetOriginalPdf(0)); // make a copy for same binning and data rep
    dataPdf.Empty();

    for(size_t i = 0; i < fDataHandle -> GetNEntries(); i++){
        EventData dat = fDataHandle -> GetEntry(i);
        dataPdf.Fill(dat);
    }

    fDataPdf = dataPdf;
    fCalculatedDataPdf = true;
}

void
BinnedNLLH::SetPdfManager(const BinnedPdfManager& man_){
    fPdfManager = man_;
    fNpdfs = man_.GetNPdfs();
}

void
BinnedNLLH::SetSystematicManager(const SystematicManager& man_){
    fSystematicManager = man_;
    fNsystematics = man_.GetNSystematics();
}

