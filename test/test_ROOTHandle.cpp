#include "../src/data/ROOTHandle.h"
#include "../src/data/DataHandler.h"
#include <iostream>
#include <TFile.h>
#include <TNtuple.h>
int main(){
   
    ROOTHandle rh("/Users/Jack/snoplus/bbplus/ntuples/fake_pu_ntup.root","T");
    std::vector<size_t> indicies(4);

    std::cout << rh.GetNEntries() << std::endl;
    //    DataHandler dh = rh.First();
    unsigned count = 0;

    while(true){
        try{
            DataHandler dh = rh.Next();
            std::vector<double> data = dh.GetData();
            for(size_t i = 0; i < data.size(); i++)
                std::cout << data[i] << "\t";
            std::cout << std::endl;
            
        }
        catch(int&){
            break;
        }
    }

    return 0;
}
