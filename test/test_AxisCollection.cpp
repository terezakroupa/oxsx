#include "AxisCollection.h"
#include "PdfAxis.h"
#include <iostream>
#include <vector>

int main(){
    AxisCollection col;
    PdfAxis a1("energy", 0, 10, 10);
    PdfAxis a2("radius", 0, 10, 10);
    
    std::vector<PdfAxis> axes;
    axes.push_back(a1);
    axes.push_back(a2);

    col.AddAxes(axes);


    std::cout << col.FlattenIndicies(std::vector<size_t>(2,9)) << std::endl;
    
    return 0;
}
