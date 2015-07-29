#include "../eval/NLLH.h"
#include "../pdf/AxisCollection.h"
#include "../pdf/PdfAxis.h"
#include "../event/Event.h"
#include "../pdf/BinnedPdf.h"

#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <vector>

#include <time.h>

int main(){
    // Get custom ntuple
    TFile f("new_ntup.root");
    TTree *t = dynamic_cast<TTree*>(f.Get("data"));

    // Specify what we will fit on 
    AxisCollection ac;
    ac.AddAxis(PdfAxis("energy", 0, 3, 100, "Energy"));
    ac.AddAxis(PdfAxis("radius", 0, 1, 100, "#frac{r_{reco}}{r_{av}}"));

    //Create the pdf
    BinnedPdf pdf("energy-radius", ac);
    std::vector<double> v(2,0);
    clock_t begin = clock();
    for(int i= 0; i < 1e6; i++){
        v[0] = 3. * (i % 1000)/ 1000.;
        v[1] = 1. * (i % 1000)/ 1000.;
        pdf.Fill(v);
    }
    std::cout << "took " << (clock() - begin)/1E6 << "seconds to fill 1e5 events" << std::endl;
    std::cout << "1e8 takes" << 1E2 * (clock() - begin)/1E6 << "seconds " << std::endl;
    pdf.Normalise();
    
    // Create the decay 
    Event ev(&pdf, "pileup");
    std::vector<Event> events;
    events.push_back(ev);

    std::vector<double> eventRates(1,1);
    NLLH test(t, events, eventRates);
    std::cout << test.Evaluate() << std::endl;
    return 0;
}
