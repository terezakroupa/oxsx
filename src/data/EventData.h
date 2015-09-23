/***********************************************************************************************/
/* Represents the observations associated with a single event.                                 */
/* Wraps a vector of the data points. Pdfs can query it with their own representation of the   */
/* data to get the relevant indicies ordered correctly.                                        */
/* For example, the data may come as (energy, radius, time). But the pdf is only interested in */
/* (radius, energy) pairs so it has the representation (1, 0).                                 */
/* EventData(4, 2, 1).ToRepresentation(pdfRep) = {2, 4}                                        */
/***********************************************************************************************/

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
