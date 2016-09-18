#ifndef __OXSX_PDF_FILLER__
#define __OXSX_PDF_FILLER__
#include <CutCollection.h>
#include <EventSystematicManager.h>
class DataSet;
class BinnedPhysDist;

class PdfFiller{
 public:
  // default is to take all the events
  static void FillPdf(BinnedPhysDist&, const DataSet&, 
                      const CutCollection& cuts_ = CutCollection(), EventSystematicManager sysMan_ = EventSystematicManager(), int nEv_ = -1);
};

#endif
