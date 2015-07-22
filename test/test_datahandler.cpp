#include "../src/data/DataHandler.h"
#include <iostream>
int main(){
    std::vector<size_t> indicies;
    indicies.push_back(0);
    indicies.push_back(2);
    DataHandler::AddRepresentation(indicies);

    std::vector<size_t> indicies2;
    indicies2.push_back(1);
    DataHandler::AddRepresentation(indicies2);
    

    std::vector<double> vals;
    vals.push_back(0.0);
    vals.push_back(1.1);
    vals.push_back(2.2);

    DataHandler dh(vals);

    std::vector<double> rep0 = dh.ToRepresentation(0);
    std::vector<double> rep1 = dh.ToRepresentation(1);

    std::cout << rep0.size() << std::endl;
    std::cout << rep1.size() << std::endl;

    std::cout << rep0[0] << "\t" << rep0[1] << std::endl;
    std::cout << rep1[0] << std::endl;
    return 0;
}
