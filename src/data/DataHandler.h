/**********************************************************************************/
/* A class to hold the relevant data for a single event and distribute it to PDFs */
/**********************************************************************************/

#ifndef __DATA_HANDLER__
#define __DATA_HANDLER__
#include <vector>

class DataHandler{
 public:
    DataHandler(const std::vector<double>& obs_);
    std::vector<double> GetData() const;
    std::vector<double> ToRepresentation(size_t iRep) const;
    static void AddRepresentation(const std::vector<size_t>& indicies_);
    
 private:
    std::vector<double> fObservations;
    static std::vector<std::vector< size_t > > fReps;
    static std::vector<size_t> fRepLens;
    
};
#endif
