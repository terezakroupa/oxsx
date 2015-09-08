/**********************************************************************************/
/* A class to hold the relevant data for a single event and distribute it to PDFs */
/**********************************************************************************/

#ifndef __DATA_HANDLER__
#define __DATA_HANDLER__
#include <vector>
class DataRepresentation;

class DataHandler{
 public:
    DataHandler(const std::vector<double>& obs_);
    std::vector<double> GetData() const;
    std::vector<double> ToRepresentation(const DataRepresentation&) const;
    
 private:
    std::vector<double> fObservations;
    
};
#endif
