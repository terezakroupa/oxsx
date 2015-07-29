#include <TNtuple.h>
#include <TBranch.h>
#include <TFile.h>
#include <iostream>
#include <time.h>

int main(){
    TFile   *f  = new TFile("./fake_pu_ntup.root");
    TNtuple *nt = dynamic_cast<TNtuple*> (f->Get("T"));
    std::cout << nt->GetEntries() << std::endl;
    TFile *out = new TFile("./new_ntup.root", "RECREATE");
    
    float e;
    float r;
    nt->SetBranchAddress("energy", &e);
    nt->SetBranchAddress("radius", &r);

    TTree *newTree = new TTree("data", "hello");

    std::vector<double> data(2,0);
    newTree->Branch("event", "", &data);
    
    const clock_t begin_time = clock();
    std::cout << nt->GetEntries() << "events" << std::endl;
    for(int i = 0; i < nt->GetEntries(); i++){
        nt->GetEntry(i);
        data[0] = e;
        data[1] = r;
        newTree->Fill();
    }
    std::cout << "took " << (clock() - begin_time)/1E6 << "s" << std::endl;
    std::cout << "or " << (clock() - begin_time)/1E6/nt->GetEntries() << "s per event" << std::endl;
    std::cout << "so 100million events takes " << 1E8 * (clock() - begin_time)/1E6/nt->GetEntries() << "s" << std::endl;
 
    // now read it out
    std::vector<double>* v = NULL;
    TBranch* b = NULL;
    newTree->SetBranchAddress("event", &v, &b);
    for(int i =0 ; i < 100; i++){
        newTree->GetEntry(i);
        //        std::cout << v->at(0) << "\t" << v->at(1) << std::endl;
    }

    out->cd();
    newTree->Write();
    
    return 0;
}
