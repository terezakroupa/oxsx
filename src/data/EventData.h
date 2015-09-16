/**********************************************************************************/
/* A class to hold the relevant data for a single event and distribute it to PDFs */
/**********************************************************************************/

#ifndef __EVENT_DATA__
#define __EVENT_DATA__
#include <vector>
class DataRepresentation;

class EventData{
 public:
    EventData(const std::vector<double>& obs_);
    std::vector<double> GetData() const;
    std::vector<double> ToRepresentation(const DataRepresentation&) const;
    
 private:
    std::vector<double> fObservations;
    
};
#endif
