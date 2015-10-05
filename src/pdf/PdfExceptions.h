#ifndef __OXSX_PDF_EXCEPTIONS__
#define __OXSX_PDF_EXCEPTIONS__
#include <string>
#include <stdexcept>

class PdfException : public std::runtime_error {
 public:
 PdfException(const std::string& errorStr) : runtime_error(errorStr) {}
};


class DimensionError : public PdfException {
 public:
 DimensionError(const std::string& errorStr) : PdfException(errorStr){}
};



class OutOfBoundsError : public PdfException{
 public:
 OutOfBoundsError(const std::string& errorStr) : PdfException(errorStr){}
};

class BinError : public PdfException{
 public:
 BinError(const std::string& errorStr): PdfException(errorStr) {}
};


class ParameterError : public PdfException{
 public:
 ParameterError(const std::string& errorStr) : PdfException(errorStr) {}
};
#endif
