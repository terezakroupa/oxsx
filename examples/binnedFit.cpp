// Fit in E and r for zero nu, two nu, b8, energy resolution, 
// energy shift and energy scale, using NLLH with constraints and markov chain/gridsearch/minuit

#include <BinnedNLLH.h>
#include <ROOTNtuple.h>
#include <iostream>
#include <PdfConverter.h>
#include <TCanvas.h>
#include <OXSXDataSet.h>
#include <DataSetGenerator.h>
#include <Minuit.h>
#include <GridSearch.h>
#include <Gaussian.h>
#include <Convolution.h>
#include <Scale.h>
#include <QuadraticConstraint.h>
#include <MetropolisHastings.h>

const bool testing = true;

int main(){
    // Set Up the binning
    AxisCollection axes;
    axes.AddAxis(PdfAxis("energy", 0, 10, 10, "Energy"));
    axes.AddAxis(PdfAxis("x", 0, 3, 10, "x"));
    
    // Are only interested in energy and radius data
    std::vector<size_t> indicies;
    indicies.push_back(0);
    indicies.push_back(1);

    DataRepresentation dRep(indicies);
        

    // Set up the binned pdfs
    BinnedPdf zeroNuPdf(axes); zeroNuPdf.SetDataRep(dRep);
    BinnedPdf twoNuPdf(axes);  twoNuPdf.SetDataRep(dRep);
    BinnedPdf b8Pdf(axes);     b8Pdf.SetDataRep(dRep);

    // and fake data set
    OXSXDataSet fakeData;
    
    
    // scoping 
    {

    // Fill the pdfs
    ROOTNtuple zeroNuMC("/Users/Jack/snoplus/sigEx/ntuples/rat4.5/exyzt/zeroNu.root", "oxsx");
    std::cout << "zero nu" << std::endl;
    for(size_t i = 0; i < zeroNuMC.GetNEntries(); i++){
        zeroNuPdf.Fill(zeroNuMC.GetEntry(i));
        if((!(i%100000)))
            std::cout << i << "/" << zeroNuMC.GetNEntries() << std::endl;
    }
    


    
    ROOTNtuple twoNuMC("/Users/Jack/snoplus/sigEx/ntuples/rat4.5/exyzt/twoNu.root", "oxsx");
    std::cout << "two nu" << std::endl;
    unsigned nEvents = twoNuMC.GetNEntries();
    if(testing)
        nEvents = 1000000;
    for(size_t i = 0; i < nEvents; i++){
        twoNuPdf.Fill(twoNuMC.GetEntry(i));
        if((!(i%100000)))
            std::cout << i << "/" << twoNuMC.GetNEntries() << std::endl;
    }
    

    
    ROOTNtuple b8NuMC("/Users/Jack/snoplus/sigEx/ntuples/rat4.5/exyzt/b8.root", "oxsx");
    std::cout << "b8" << std::endl;
    for(size_t i = 0; i < b8NuMC.GetNEntries(); i++)
        b8Pdf.Fill(b8NuMC.GetEntry(i));

    std::vector<double>       rates;
    std::vector<DataSet*> handles;
    handles.push_back(&zeroNuMC);  rates.push_back(60);
    handles.push_back(&twoNuMC);   rates.push_back(50);
    handles.push_back(&b8NuMC);    rates.push_back(100);


    DataSetGenerator generator;
    generator.SetDataSets(handles);
    generator.SetExpectedRates(rates);
    fakeData = generator.ExpectedRatesDataSet();
    }
    
    twoNuPdf.Normalise();
    zeroNuPdf.Normalise();
    b8Pdf.Normalise();

    std::cout << twoNuPdf.Integral() << std::endl;
    std::cout << zeroNuPdf.Integral() << std::endl;
    std::cout << b8Pdf.Integral() << std::endl;


    // Now smear with a gaussian energy resolution
    Gaussian gaussianPdf(0, 0.5);
    Convolution smearer;
    
    DataRepresentation dRep2(std::vector<size_t>(1,0));

    smearer.SetPdf(&gaussianPdf);
    smearer.SetAxes(axes);
    smearer.SetDataRep(dRep2);
    smearer.SetPdfDataRep(dRep);

    //////////////////////////////////////////////////
    // BinnedPdf sm_twoNuPdf = smearer(twoNuPdf);   //
    // BinnedPdf sm_b8Pdf = smearer(b8Pdf);         //
    // BinnedPdf sm_zeroNuPdf = smearer(zeroNuPdf); //
    //////////////////////////////////////////////////
    //

    // energy scale error
    Scale scaler(0); // in energy
    scaler.SetAxes(axes);
    scaler.SetDataRep(dRep2);
    scaler.SetPdfDataRep(dRep);    

    // print out
    TH1D twoNuTH1  = PdfConverter::ToTH1D(PdfConverter::Marginalise(twoNuPdf, 
                                                                    std::vector<size_t>(1,0)));

    TH1D zeroNuTH1  = PdfConverter::ToTH1D(PdfConverter::Marginalise(zeroNuPdf, 
                                                                    std::vector<size_t>(1,0)));
    TH1D b8TH1  = PdfConverter::ToTH1D(PdfConverter::Marginalise(b8Pdf, 
                                                                    std::vector<size_t>(1,0)));


    TCanvas can;
    twoNuTH1.SetLineColor(2);
    b8TH1.SetLineColor(5);
    
    zeroNuTH1.Draw();
    twoNuTH1.Draw("same");
    b8TH1.Draw("same");

    can.SaveAs("test.root");

    // Set up the binned fit for NLLH
    BinnedPdfManager pManager;
    pManager.AddPdf(zeroNuPdf);
    pManager.AddPdf(twoNuPdf);
    pManager.AddPdf(b8Pdf);
    
    SystematicManager sManager;
    sManager.Add(&smearer);
    sManager.Add(&scaler);

    BinnedNLLH lh;
    lh.SetPdfManager(pManager);
    lh.SetSystematicManager(sManager);
    lh.SetDataSet(&fakeData);

    //Fit with a grid search
    GridSearch gs(&lh);
    std::vector<double> minima(3,45);
    minima.push_back(0);
    minima.push_back(0.0000000001);
    minima.push_back(0.98);
    
    std::vector<double> maxima(3,105);
    maxima.push_back(0.2);
    maxima.push_back(0.1);
    maxima.push_back(1.02);


    std::vector<double> steps(3, 5);
    steps.push_back(0.01);
    steps.push_back(0.005);
    steps.push_back(0.001);


    gs.SetMaxima(maxima);
    gs.SetMinima(minima);
    gs.SetStepSizes(steps);
    // Grid search can be 1000x faster or more because it steps through normalisations first - fewer
    // convolutions -> the dominant process (~70%). BUT, requires many many more steps
    //    gs.Optimise();     

    
    std::vector<double> bestFit = gs.GetFitResult().GetBestFit();
    for(size_t i = 0; i < bestFit.size(); i++)
        std::cout << bestFit.at(i) << "\t";
    std::cout << std::endl;

    // now fit with minuit
    Minuit min(&lh);
    std::vector<double> initVals;
    initVals.push_back(60);
    initVals.push_back(50);
    initVals.push_back(100);
    initVals.push_back(0);
    initVals.push_back(0.5);
    initVals.push_back(1.0);

    std::vector<double> initErrs;
    initErrs.push_back(5);
    initErrs.push_back(5);
    initErrs.push_back(5);
    initErrs.push_back(0);
    initErrs.push_back(-0.1);
    initErrs.push_back(0.001);

    min.SetInitialValues(initVals);
    min.SetInitialErrors(initErrs);

    min.SetMinima(minima);
    min.SetMaxima(maxima);

    min.Initialise();
    
    //    min.Optimise();

    bestFit = min.GetFitResult().GetBestFit();
    for(size_t i = 0; i < bestFit.size(); i++)
        std::cout << bestFit.at(i) << "\t";
    std::cout << std::endl;   


    // Now do it with Metropolis Hastings
    MetropolisHastings mh(&lh);
    mh.SetMinima(minima);
    mh.SetMaxima(maxima);
    mh.SetSigmas(steps);
    mh.SetMaxIter(1000000);
    mh.Optimise();


    return 0;
}
