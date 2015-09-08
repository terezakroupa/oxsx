/*******************************************************************************************/
/* Light weight class to represent a particular combination of the data for a single event */
/*******************************************************************************************/
#ifndef __DATA_REPRESENTATION__
#define __DATA_REPRESENTATION__
#include <vector>
#include <string>

class DataRepresentation{
 public:    
    DataRepresentation() {}
    DataRepresentation(const std::vector<size_t>& indicies_);
    DataRepresentation(const DataRepresentation&);
    ~DataRepresentation() {}

    std::vector<size_t> GetIndicies() const; 
    void SetIndicies(const std::vector<size_t>& indicies_); 

    std::string GetName() const;
    void SetName(const std::string& name_);

    size_t GetIndex(size_t indexNum_) const;
    size_t GetLength() const;

 private:
    std::vector<size_t> fIndicies;
    std::string fName;
    size_t fLen;
};
#endif
