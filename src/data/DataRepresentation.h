/*******************************************************************************************/
/* Light weight class to represent a particular combination of the data for a single event */
/*******************************************************************************************/
#ifndef __DATA_REPRESENTATION__
#define __DATA_REPRESENTATION__
#include <vector>
#include <string>
#include <utility>

class DataRepresentation{
 public:    
    DataRepresentation() {}
    DataRepresentation(const std::vector<size_t>& indices_);
    DataRepresentation(size_t index_);
    DataRepresentation(const DataRepresentation&);
    
    ~DataRepresentation() {}

    std::vector<size_t> GetIndices() const; 
    void SetIndices(const std::vector<size_t>& indices_); 

    std::string GetName() const;
    void SetName(const std::string& name_);

    size_t GetIndex(size_t indexNum_) const;
    size_t GetNObservables() const;
    
    size_t GetDataIndexPos(size_t dataIndex_) const; // where is data index x in this representation
    // Call this something else
    std::vector<size_t> GetRelativeIndices(const DataRepresentation&) const; 

 private:
    std::vector<size_t> fIndices;
    std::vector< std::pair<size_t, size_t> > fInverse;
    std::string fName;
    size_t fNObservables;
};
#endif
