/**************************************************************/
/* Static Utility class for doing a variety of pdfconversions */
/**************************************************************/
#ifndef __PDF_CONVERTER__
#define __PDF_CONVERTER__


class BinnedPhysDist;
class PDF;
class AxisCollection;
class Histogram;
class TH2D;
class TH1D;

class PdfConverter{
 public:
    static BinnedPhysDist ToBinnedPhysDist(const PDF&, const AxisCollection& axes_);
    static TH1D      ToTH1D(const BinnedPhysDist&, const bool widthCorrect_ = false);
    static TH1D      ToTH1D(const Histogram&, const bool widthCorrect_ = false);
	static TH2D      ToTH2D(const Histogram&, const bool widthCorrect_ = false);
	static TH2D      ToTH2D(const BinnedPhysDist&, const bool widthCorrect_ = false);
};
#endif
