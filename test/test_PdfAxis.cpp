#include "PdfAxis.h"
#include <iostream>

int main(){
    PdfAxis a1("test1", 0, 10, 10);
    for(size_t i = 0; i < a1.GetNBins(); i++){
        std::cout << i << std::endl;
    }

    std::cout << a1.FindBin(-1) << "\t" << a1.FindBin(11) << std::endl;
    return 0;
}
