#include <ChiSquare.h>
#include <DataHandle.h>

double
ChiSquare::Evaluate(){
    // the first time this is called, bin data into a pdf
    if (!fCalculatedDataPdf){
        BinData();
        fCalculatedDataPdf = true;
    }
    
    // Adjust Systematics                                                                               
    fSystematicManager.SetParameters(fSystematicParams);

    // Apply systematics
    fPdfManager.ApplySystematics(fSystematicManager.GetSystematics());
    
    // Set Normalisations                                   
    fPdfManager.SetNormalisations(fNormalisations);

    // Now calculate the ChiSquared
    double chiSquare = 0;
    for(size_t i = 0; i < fDataPdf.GetNBins(); i++){
        double expected = fPdfManager.Probability(fDataPdf.GetAxes().GetBinCentre(i));
        double deviation = fDataPdf.GetBinContent(i) - expected;
        chiSquare += deviation * deviation / expected; // poisson errors 
    }

    return chiSquare;
}


void
ChiSquare::BinData(){

    BinnedPdf dataPdf(fPdfManager.GetOriginalPdf(0)); // make a copy for same binning and data rep
    dataPdf.Empty();
    
    for(size_t i = 0; i < fDataHandle -> GetNEntries(); i++){
        dataPdf.Fill(fDataHandle -> GetEntry(i));
    }
    
    fDataPdf = dataPdf;
}
