// A simple fit in energy for signal and a background        
#include <BinnedPdf.h>        
#include <ROOTNtuple.h>        
#include <BinnedNLLH.h>        
#include <GridSearch.h>        
         
int main(){        
    ////////////////////        
    // 1. Set Up PDFs //        
    ////////////////////        
         
    // Set up binning        
    AxisCollection axes;        
    axes.AddAxis(PdfAxis("energy", 2, 3, 10, "Energy"));               
         
    // Only interested in first bit of data ntuple        
    DataRepresentation dataRep(0);        
         
    // Set up pdf with these bins in this observable        
    BinnedPdf bgPdf(axes);      bgPdf.SetDataRep(dataRep);        
    BinnedPdf signalPdf(axes);  signalPdf.SetDataRep(dataRep);        
         
    std::cout << "Initialised Pdfs" << std::endl;        
         
    /////////////////////////////////////        
    // 2. Fill with data and normalise //        
    /////////////////////////////////////        
         
    ROOTNtuple bgMC("filename.root", "treename");        
    ROOTNtuple signalMC("filename.root", "treename");        
         
    for(size_t i = 0; i < 10; i++){        
        bgPdf.Fill(bgMC.GetEntry(i));        
    }        
          
    for(size_t i = 0; i < 10; i++){        
        signalPdf.Fill(signalMC.GetEntry(i));        
    }        
             
         
    bgPdf.Normalise();        
    signalPdf.Normalise();        
         
    std::cout << "Filled pdfs " << std::endl;        
         
    ////////////////////////////        
    // 3. Set Up LH function  //        
    ////////////////////////////        
         
    BinnedNLLH lhFunction;        
    lhFunction.SetDataSet(&signalMC); // initialise withe the data set        
    lhFunction.AddPdf(bgPdf);        
    lhFunction.AddPdf(signalPdf);        
    
         
    std::cout << "Built LH function " << std::endl;        
         
    // Set up the optimisation        
    GridSearch gSearch(&lhFunction);        
             
    std::vector<double> minima(2, 0);        
    std::vector<double> maxima(2, 100);        
    std::vector<double> stepsizes(2, 1);        
         
    gSearch.SetMaxima(maxima);        
    gSearch.SetMinima(minima);        
    gSearch.SetStepSizes(stepsizes);        
    
         
    ////////////        
    // 4. Fit //        
    ////////////        
    gSearch.Optimise();        
         
    std::vector<double> fit = gSearch.GetFitResult().GetBestFit();        
             
    std::cout << "Best Fit: " << std::endl;        
    for(size_t i = 0; i < fit.size(); i++)        
        std::cout << fit.at(i) << "\t";        
    std::cout << std::endl;        
    
    return 0;        
}
