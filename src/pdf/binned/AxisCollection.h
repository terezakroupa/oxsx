/******************************************************************************************************/
/* A group of Axes that defines the binning for a pdf.                                                */
/* Each bin is assigned a global bin ID, switch between this global ID and the indicies in each       */
/* axis using FlattenIndicies and UnpackIndicies                                                      */
/******************************************************************************************************/

#ifndef __AXIS_COLLECTION__
#define __AXIS_COLLECTION__

#include <PdfAxis.h>
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
    size_t  UnflattenIndex(size_t index_, size_t dim_)  const;
    std::vector<size_t> UnpackIndicies(size_t index_) const;

    void GetBinCentre(size_t bin_, std::vector<double>& output_) const;
    void GetBinLowEdges(size_t bin_, std::vector<double>& output_) const;
    void GetBinHighEdges(size_t bin_, std::vector<double>& output_) const;

    double GetBinLowEdge(size_t bin_, size_t dim_) const;
    double GetBinHighEdge(size_t bin_, size_t dim_) const;
    double GetBinCentre(size_t bin_, size_t dim_) const;
    
 private:
    std::vector<PdfAxis> fAxes;
    std::vector<size_t> fAxisNbins;
    size_t fNBins;
    size_t fNDimensions;
    
    void    CountBins();
    bool    HasAxis(const std::string& name_);
};

#endif
