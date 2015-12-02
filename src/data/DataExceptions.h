#ifndef __OXSX_DATA_EXCEPTIONS__
#define __OXSX_DATA_EXCEPTIONS__
#include <string>
#include <stdexcept>

class DataException : public std::runtime_error{
 public:
 DataException(const std::string& errorStr) : std::runtime_error(errorStr) {}
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
class ROOTError : public DataException {
 public:
 ROOTError(const std::string& error_str): DataException(error_str){};
};

// HDF5 IO
class IOError : public DataException{
 public:
 IOError(const std::string& error_str): DataException(error_str){};
};
#endif
