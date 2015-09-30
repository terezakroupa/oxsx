/******************************************************************************************************/
/* A binned pdf is a combination of an axis collection that defines the binning and a single vector of*/
/* bin contents, indexed by the corresponding global bin ID.                                          */
/* Each pdf has a data representation, that tells it which event variables it is interested in from th*/
/* EventData class                                                                                    */
/******************************************************************************************************/

#ifndef __BINNED_PDF__
#define __BINNED_PDF__
#include <AxisCollection.h>
#include <Pdf.h>
#include <vector>

class BinnedPdf : public Pdf{
 public:
    BinnedPdf() {}
    BinnedPdf(const AxisCollection& axes_);
    BinnedPdf(const BinnedPdf& other_);
    
    virtual double operator() (const std::vector<double>& vals_) const;
    virtual double Integral()  const;
    virtual void   Normalise();
    virtual  Pdf*  Clone() const; // required for pdf outer product
    
    void   Fill(const std::vector<double>& vals_, double weight_ = 1);
    void   Fill(const EventData& data_, double weight_ = 1);

    size_t FindBin(const std::vector<double>& vals_) const;
    size_t FindBin(const EventData& data_) const;

    std::vector<size_t> UnpackIndicies(size_t bin_) const;
    size_t FlattenIndicies(const std::vector<size_t>& indicies_) const;

    const AxisCollection& GetAxes() const;
    void  SetAxes(const AxisCollection& axes_);

    std::vector<double> GetData() const; 
    void SetData(const std::vector<double>& data_);     


    double GetBinContent(size_t bin_) const;
    size_t GetNBins() const;
    void   AddBinContent(size_t bin_, double content_);

    void   Empty();
    
 private:
    AxisCollection fAxes;
    std::vector<double> fBinContents;
    size_t fNBins;
};
#endif
