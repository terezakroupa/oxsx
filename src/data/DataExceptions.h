#ifndef __OXSX_DATA_EXCEPTIONS__
#define __OXSX_DATA_EXCEPTIONS__
#include <string>

class DataException : public std::runtime_error{
 public:
 DataException(const std::string& errorStr) : runtime_error(errorStr) {}
};


// Thrown when an object queries the event data with an incompatible representation
class RepresentationError :  public DataException{
 public:
 RepresentationError(const std::string& errorStr) : DataException(errorStr) {}
};


// Thrown when non existent data is requested
class DataNotFoundError : public DataException{
 public:
 DataNotFoundError(const std::string& errorStr) : DataException(errorStr) {}
};

// error reading root file
class ROOTError : public std::runtime_error {
 public:
 ROOTError(const std::string& error_str):runtime_error(error_str){};
};


#endif
