#include <iostream>
#include "BinnedPdf.h"
#include "AxisCollection.h"
#include <fstream>

int main(){
    AxisCollection col;
    col.AddAxis(PdfAxis("energy", 0, 10, 10));
    col.AddAxis(PdfAxis("radius", 0, 20, 10));

    BinnedPdf pdf("test", col);
    for(int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            double x = 0.01 + i * 1./10;
            double y = 2 * x;

            std::vector<double> p;
            p.push_back(x);
            p.push_back(y);
            pdf.Fill(p);
        }
    }
    
    
    BinnedPdf projection  = pdf.Marginalise(0);
    BinnedPdf projection2 = pdf.Marginalise(1);
   

    std::vector<double> p1 = projection.GetRawData();
    std::vector<double> p2 = projection2.GetRawData();

    std::ofstream f;
    f.open("p1.txt");
    for(size_t i = 0; i < p1.size(); i++)
        f << p1[i]<< "\n";
    f << "\n";
    f.close();

    std::ofstream f2;
    f2.open("p2.txt");
    for(size_t i = 0; i < p2.size(); i++)
        f2 << p2[i]<< "\n";
    f2.close();

    return 0;
}
