#include <PdfFiller.h>
#include <CutCollection.h>
#include <BinnedPdf.h>
#include <DataSet.h>
#include <iostream>
void
PdfFiller::FillPdf(BinnedPdf& pdf_, const DataSet& data_, const CutCollection& cuts_, int nEv_){
  if(nEv_ < 0)
	nEv_ = data_.GetNEntries();
  for(size_t i = 0; i < nEv_; i++){
	if(!(i% 10000000))
	  std::cout << i << "/" << nEv_ << std::endl;
    EventData ev = data_.GetEntry(i);	
    if(cuts_.PassesCuts(ev))
      pdf_.Fill(ev);
  }
}
