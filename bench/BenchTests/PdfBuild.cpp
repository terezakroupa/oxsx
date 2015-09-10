#include <Bench.h>
#include <AxisCollection.h>
#include <BinnedPdf.h>
#include <ROOTHandle.h>
#include <iostream>

const std::string fileName = "/Users/Jack/snoplus/bbplus/ntuples/fake_pu_ntup.root";
const std::string treeName = "T";

void BuildAPdf(){
    // Build the pdf
    AxisCollection ax;
    ax.AddAxis(PdfAxis("energy", 0, 3, 100));
    ax.AddAxis(PdfAxis("radius", 0, 1, 100));
    ax.AddAxis(PdfAxis("psd", 0, 1, 100));
    ax.AddAxis(PdfAxis("psd2", 0, 1, 100));
    BinnedPdf pdf(ax);
    std::vector<size_t> indicies;
    indicies.push_back(0);
    indicies.push_back(1);
    indicies.push_back(2);
    indicies.push_back(3);
    pdf.SetDataRep(DataRepresentation(indicies));


    // Get the data
    ROOTHandle rHandle(fileName, treeName);
    unsigned nEntries = rHandle.GetNEntries();
    std::cout << nEntries << " Entries to fill" << std::endl;
    // Fill the Pdf
    for(size_t i = 0; i < nEntries; i++){
        pdf.Fill(rHandle.GetEntry(i));
    }
    
    return;
}


int main(){
    Bench b(&BuildAPdf, "Filling ");
    b.TimeRepetitions(100);
    b.PrintResult();
    return 0;

}
