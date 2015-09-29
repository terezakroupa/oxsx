#include <ROOTNuple.h>
#include <DataSetGenerator.h>

int main(){
    // (filename, tree name)
    ROOTNtuple zeroNuMC("/Users/Jack/snoplus/sigEx/ntuples/rat4.5/exyzt/zeroNu.root", "oxsx");
    ROOTNtuple twoNuMC("/Users/Jack/snoplus/sigEx/ntuples/rat4.5/exyzt/twoNu.root", "oxsx");
    ROOTNtuple b8NuMC("/Users/Jack/snoplus/sigEx/ntuples/rat4.5/exyzt/b8.root", "oxsx");

    // DataSetGenerator
    DataSetGenerator dataGen;
    dataGen.AddDataSet(&zeroNuMC, 5);  // second arg is the expected rate
    dataGen.AddDataSet(&twoNuMC, 50);
    dataGen.AddDataSet(&b8NuMC, 100);

    // Generate a data set
    OXSXDataSet fakeData  = dataGen.PoissonFluctuatedDataSet();
    OXSXDataSet fakeData2 = dataGen.ExpectedRatesDataSet();
    
    
    return 0;
}
