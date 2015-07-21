/********************************************************************************************/
/* This class controls the indexing of the dynamic dimension array that underlies each pdf */
/********************************************************************************************/

#ifndef __AXIS_COLLECTION__
#define __AXIS_COLLECTION__

#include "PdfAxis.h"
#include <vector>
#include <exception>

class AxisCollection{
    
 public:
    AxisCollection():fNDimensions(0), fNBins(0){}
    size_t  FindBin(const std::vector<double>& vals_) const;
    size_t  GetNBins() const;
    void    AddAxis(const PdfAxis& axis_);
    void    AddAxes(const std::vector<PdfAxis>& axes_);
    const PdfAxis& GetAxis(size_t axisIndex_) const;
    
    size_t GetNDimensions() const;
    size_t FlattenIndicies(const std::vector<size_t>& indicies_) const;
    std::vector<size_t> UnpackIndicies(size_t index_) const;

 private:
    std::vector<PdfAxis> fAxes;
    std::vector<size_t> fAxisNbins;
    size_t fNBins;
    size_t fNDimensions;
    
    void    CountBins();
    size_t  UnflattenIndex(size_t index_, size_t dim_)  const;
    bool    HasAxis(const std::string& name_);
};



class DimensionError : public std::runtime_error {
 public:
 DimensionError(const std::string& error_str):runtime_error(error_str){};
};

class OutOfBoundsError : public std::runtime_error {
 public:
 OutOfBoundsError(const std::string& error_str):runtime_error(error_str){};
};

#endif
