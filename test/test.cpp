#include "../src/eval/NLLH.h"
#include "../src/optimise/GridSearch.h"

#include "../src/pdf/PdfAxis.h"
#include "../src/pdf/AxisCollection.h"
#include "../src/pdf/BinnedPdf.h"
#include "../src/event/Event.h"

#include <TTree.h>
#include <TFile.h>

#include <iostream>
#include <time.h>
const std::string dataSet   = "new_ntup.root";
const std::string v2PdfSet  = "";
const std::string b8PdfSet  = "";

int main(){

    // Build the observables
    AxisCollection col;
    PdfAxis a1("energy", 0, 3, 90);
    PdfAxis a2("radius", 0, 1, 10);    
    col.AddAxis(a1);
    col.AddAxis(a2);
    
    // Build the pdfs with the same axes
    BinnedPdf b8Pdf("b8", col);
    BinnedPdf v2Pdf("v2", col);

    // fill the pdfs with the events and normalise
    for(size_t i = 0; i < 1000; i++){
        for(size_t j = 0; j < 1000; j++){
        std::vector<double> v;
        v.push_back(3 * i * 1/1000.);
        v.push_back(j * 1/1000.);
        b8Pdf.Fill(v);
        v2Pdf.Fill(v);
        }
    }

    b8Pdf.Normalise();
    v2Pdf.Normalise();
    std::cout << b8Pdf.Integral() << std::endl;
    // build the event types
    Event b8(&b8Pdf, "b8", "{}^{8}B");
    Event v2(&v2Pdf, "v2", "2#nu#beta#beta");

    // Now set up the fit
    TFile f(dataSet.c_str());
    TTree* data = dynamic_cast<TTree*> (f.Get("data"));
    NLLH nllh(data);
    nllh.AddEventType(b8, 10);
    nllh.AddEventType(v2, 10);
    time_t begin = clock();
    for(unsigned i = 0; i < 100; i++)
        nllh.Evaluate();
    std::cout << "100 LH calc took " <<  (clock() - begin) / 1e6  << std::endl;
    std::cout << "--> 1 LH calc took " <<  (clock() - begin) / 1e8  << std::endl;
    return 0;
}
