#ifndef __BINNED_PDF__
#define __BINNED_PDF__
#include <AxisCollection.h>
#include <Pdf.h>
#include <vector>

class BinnedPdf : public Pdf{
    // fixme. dont repeat all of hthe axis methods, just return a reference to the axis collection??
 public:
    BinnedPdf() {}
    BinnedPdf(const AxisCollection& axes_);
    BinnedPdf(const BinnedPdf& other_);
    
    virtual double operator() (const std::vector<double>& vals_) const;
    virtual double Integral()  const;
    virtual void   Normalise();
    virtual  Pdf*  Clone() const;
    
    void   Fill(const std::vector<double>& vals_);
    void   Fill(const DataHandler& data_);

    size_t FindBin(const std::vector<double>& vals_) const;
    std::vector<size_t> UnpackIndicies(size_t bin_) const;
    size_t FlattenIndicies(const std::vector<size_t>& indicies_) const;

    const AxisCollection& GetAxes() const;
    void  SetAxes(const AxisCollection& axes_);

    std::vector<double> GetData() const {return fBinContents;}
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
