#include <ChiSquare.h>
#include <DataSet.h>
#include <sstream>
#include <SystematicExceptions.h>

double
ChiSquare::Evaluate(){
    // the first time this is called, bin data into a pdf
    if (!fCalculatedDataPdf){
        BinData();
        fCalculatedDataPdf = true;
    }
    
    // Construct
    fSystematicManager.Construct();

    // Apply systematics
    fPdfManager.ApplySystematics(fSystematicManager);
    
    // Now calculate the ChiSquared
    double chiSquare = 0;
    std::vector<double> binCentre(fDataPdf.GetNDims());
    for(size_t i = 0; i < fDataPdf.GetNBins(); i++){
        fDataPdf.GetAxes().GetBinCentres(i, binCentre);
        double expected = fPdfManager.Probability(binCentre);
        double deviation = fDataPdf.GetBinContent(i) - expected;
        chiSquare += deviation * deviation / expected; // poisson errors 
    }

    return chiSquare;
}


void
ChiSquare::BinData(){

    BinnedPdf dataPdf(fPdfManager.GetOriginalPdf(0)); // make a copy for same binning and data rep
    dataPdf.Empty();
    
    for(size_t i = 0; i < fDataSet -> GetNEntries(); i++){
        dataPdf.Fill(fDataSet -> GetEntry(i));
    }
    
    fDataPdf = dataPdf;
}


void
ChiSquare::RegisterFitComponents(){
    fComponentManager.AddComponent(&fPdfManager);
    for(size_t i = 0; i < fSystematicManager.GetSystematics().size(); i++)
        fComponentManager.AddComponent(fSystematicManager.GetSystematics().at(i));
}


void
ChiSquare::SetParameters(const std::vector<double>& params_){
    RegisterFitComponents();
    try{
        fComponentManager.SetParameters(params_);
    }
    catch(const WrongNumberOfParameters&){
        std::stringstream ss;
        ss << "ChiSquare expected " << GetParameterCount()
           << " parameters, got " << params_.size();
        throw WrongNumberOfParameters(ss.str());
    }
}

std::vector<double> 
ChiSquare::GetParameters() const{
    return fComponentManager.GetParameters();
}

int 
ChiSquare::GetParameterCount() const{
    return fComponentManager.GetTotalParameterCount();
}

std::vector<std::string>
ChiSquare::GetParameterNames() const{
    return fComponentManager.GetParameterNames();
}
