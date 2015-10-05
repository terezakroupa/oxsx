#ifndef __OXSX_SYSTEMATIC_EXCEPTIONS__
#define __OXSX_SYSTEMATIC_EXCEPTIONS__
#include <string>
#include <stdexcept>

class SystematicException : public std::runtime_error{
 public:
 SystematicException(const std::string& errStr) : runtime_error(errStr) {}
};


class InvalidSystematicParameter : public SystematicException{
 public:
 InvalidSystematicParameter(const std::string& errStr) : SystematicException(errStr) {}
};

class  WrongNumberOfParameters : public SystematicException{
 public:
 WrongNumberOfParameters(const std::string& errStr) : SystematicException(errStr) {}

};

class  InitialisationError : public SystematicException{
 public:
 InitialisationError(const std::string& errStr) : SystematicException(errStr) {}

};

#endif
