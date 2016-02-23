#include <ROOTNuple.h>        
#include <DataSetGenerator.h>        
         
int main(){        
    // (filename, tree name)        
    ROOTNtuple zeroNuMC("<filename1>", "treename");        
    ROOTNtuple twoNuMC( "<filename2>", "treename");        
    ROOTNtuple b8NuMC(  "<filename3>", "treename");
    
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
