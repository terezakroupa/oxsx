#ifndef __OXSX_PDF_FILLER__
#define __OXSX_PDF_FILLER__
class CutCollection;
class DataSet;
class BinnedPdf;

class PdfFiller{
 public:
  // default is to take all the events
  static void FillPdf(BinnedPdf&, const DataSet&, const CutCollection& cuts_, int nEv_ = -1);
};

#endif
