#include <ROOTMultiPlot.h>
#include <PdfConverter.h>
#include <Exceptions.h>
#include <BinnedPdf.h>
#include <THStack.h>
#include <iostream>

//FIXME: add marginalisations for higher D pdfs
const unsigned 
ROOTMultiPlot::fNcolors = 7;
const int
ROOTMultiPlot::fColorScheme[fNcolors] = {kRed, kBlue, kViolet, 
					 kOrange, kBlue, kBlack,
					 kMagenta};
					 

void
ROOTMultiPlot::AddPdf(const BinnedPdf& pdf_, const std::string name_){
  size_t nDims = pdf_.GetNDims();
  if (nDims != 1)
    throw DimensionError("ROOTMultiPlot::Added dim != 1 binned pdf!");
  
  TH1D rootHist = PdfConverter::ToTH1D(pdf_);
  rootHist.SetDirectory(0);
  rootHist.GetXaxis()->SetTitle(pdf_.GetAxes().GetAxis(0).GetLatexName().c_str());
  AddPdf(rootHist, name_);
}

void 
ROOTMultiPlot::AddPdf(const TH1D& pdf_, const std::string name_){
  fHists.push_back(pdf_);
  fNames.push_back(name_);
  fConstructed = false;
}

void
ROOTMultiPlot::SaveAs(const std::string& filename_){
  if(!fConstructed)
    Construct();
  
  fCanvas.SaveAs(filename_.c_str());
}


TCanvas&
ROOTMultiPlot::GetCanvas(){
  if(!fConstructed)
    Construct();
  
  return fCanvas;
}


void
ROOTMultiPlot::Construct(){
  if(!fHists.size())
    return;
    
  // Setsizes
  double maxX = 0;
  double minX = 0;

  for(size_t i = 0; i < fHists.size(); i++){
    double xUp = fHists.at(i).GetMaximum();    
    double xLow = fHists.at(i).GetMinimum();

    if(xUp > maxX || !i)
      maxX = xUp;
    if(xLow < minX || !i)
      maxX = xUp;
  }
  double span = maxX - minX;
  for(size_t i = 0; i < fHists.size(); i++){
    //    fHists.at(i).GetXaxis() -> SetRange(minX - 0.1 * span, maxX + 0.1 * span);
    continue;
  }
  
  // draw with legend
  fCanvas.Clear();
  fLegend.Clear();
  fCanvas.cd();

  for(size_t i = 0; i < fNames.size(); i++){
    fLegend.AddEntry(&fHists.at(i), fNames.at(i).c_str());
    fHists[i].SetLineColor(fColorScheme[i %fNcolors]);
  }

  if(fStacked)
	ConstructStacked();
  else
	ConstructOverlay();

  if(fDrawLegend)
    fLegend.Draw("same");
  
  fConstructed = true;
}

void
ROOTMultiPlot::SetStacked(bool b_){
  fStacked = b_;
  fConstructed = false;
}

void
ROOTMultiPlot::ConstructOverlay(){
  for(size_t i = 0; i < fNames.size(); i++){
    fHists.at(i).Draw("same");	
  }
}

void
ROOTMultiPlot::ConstructStacked(){
  THStack stack("", "");
  for(size_t i = 0; i < fNames.size(); i++)
	stack.Add(&fHists.at(i));
  stack.Draw();
}
