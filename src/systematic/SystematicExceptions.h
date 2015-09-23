#ifndef __OXSX_SYSTEMATIC_EXCEPTIONS__
#define __OXSX_SYSTEMATIC_EXCEPTIONS__
#include <string>

class SystematicException : public runtime_error{
 public:
 SystematicException(const std::string& errStr) : runtime_error(errStr) {}
};


class InvalidSystematicParameter : public SystematicException{
 public:
 InvalidSystematicParameter(const std::string& errStr) : SystematicException(errStr) {}
    
};
#endif
