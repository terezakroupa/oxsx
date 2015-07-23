#include "../src/pdf/binned/PdfAxis.h"
#include <iostream>

int main(){
    PdfAxis test("test", -10, 10, 100,"te^{s}t");
    
    for(size_t i = 0; i < test.GetNBins(); i++)
        std::cout << i << "\t" << 
            test.GetBinLowEdge(i) << "\t" << test.GetBinHighEdge(i) << std::endl;

    std::cout << "-200 goes in " << test.FindBin(-200) << std::endl;
    std::cout << "0 goes in " << test.FindBin(0) << std::endl;
    std::cout << "200 goes in " << test.FindBin(200) << std::endl;
    return 0;
}
