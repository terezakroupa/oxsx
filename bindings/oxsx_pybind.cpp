#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // for auto iterable conversion

#include <FitComponent.h>
#include <FitParameter.h>

#include <Function.h>
#include <IntegrableFunction.h>
#include <Gaussian.h>
//#include <Heaviside.h>

#include <AxisCollection.h>
#include <Histogram.h>
#include <PdfAxis.h>
#include <BoolCut.h>
#include <BoxCut.h>
#include <Cut.h>
#include <CutCollection.h>
#include <LineCut.h>
#include <DataRepresentation.h>
#include <DataSet.h>
#include <DataSetGenerator.h>
#include <EventData.h>
#include <IO.h>
#include <OXSXDataSet.h>
#include <ROOTNtuple.h>
#include <BinnedPdfManager.h>
#include <BinnedPdfShrinker.h>
#include <PdfManager.h>
#include <SystematicManager.h>
#include <BayesIntervalCalc.h>
#include <FitResult.h>
#include <GridSearch.h>
#include <MetropolisHastings.h>
#include <Minuit.h>
#include <Optimiser.h>
#include <AnalyticPdf.h>
#include <CompositePdf.h>
#include <Pdf.h>
#include <PdfConverter.h>
#include <BinnedPdf.h>
#include <PdfMapping.h>
#include <armadillo>
#include <SpectralFitPdf.h>
#include <Rand.h>
#include <Convolution.h>
#include <Scale.h>
#include <Systematic.h>
#include <BinnedNLLH.h>
#include <ChiSquare.h>
#include <QuadraticConstraint.h>
#include <TestStatistic.h>

#include <TH2D.h>
#include <TH1D.h>

//namespace py = pybind11;
using namespace pybind11;

PYBIND11_PLUGIN(oxsx){

  module m("oxsx", "Python bindings for OXSX");

#include <core/FitComponent.wrap>
#include <core/FitParameter.wrap>

#include <core/function/Function.wrap>
#include <core/function/IntegrableFunction.wrap>
#include <core/function/Gaussian.wrap>
  //#include <core/function/Heaviside.wrap> // not included yet as pure virtual methods of base not implemented

#include <core/histogram/PdfAxis.wrap>
#include <core/histogram/AxisCollection.wrap>
#include <core/histogram/Histogram.wrap>

#include <cut/Cut.wrap>
#include <cut/BoolCut.wrap>
#include <cut/BoxCut.wrap>
#include <cut/CutCollection.wrap>
#include <cut/LineCut.wrap>

#include <data/DataRepresentation.wrap>
#include <data/DataSet.wrap>
#include <data/DataSetGenerator.wrap>
#include <data/EventData.wrap>
#include <data/ROOTNtuple.wrap>
#include <data/IO.wrap>
#include <data/OXSXDataSet.wrap>

#include <fitutil/BinnedPdfManager.wrap>
#include <fitutil/BinnedPdfShrinker.wrap>
#include <fitutil/PdfManager.wrap>
#include <fitutil/SystematicManager.wrap>

#include <interval/BayesIntervalCalc.wrap>

#include <optimise/Optimiser.wrap>
#include <optimise/FitResult.wrap>
#include <optimise/GridSearch.wrap>
#include <optimise/MetropolisHastings.wrap>
#include <optimise/Minuit.wrap>

#include <pdf/Pdf.wrap>
#include <pdf/AnalyticPdf.wrap>
#include <pdf/CompositePdf.wrap>
#include <pdf/PdfConverter.wrap>
#include <pdf/binned/BinnedPdf.wrap>
#include <pdf/binned/PdfMapping.wrap>
#include <pdf/binned/SpectralFitPdf.wrap>

#include <rand/Rand.wrap>

#include <systematic/Systematic.wrap>
#include <systematic/Convolution.wrap>
#include <systematic/Scale.wrap>

  
#include <teststat/TestStatistic.wrap>
#include <teststat/QuadraticConstraint.wrap>
#include <teststat/BinnedNLLH.wrap>
#include <teststat/ChiSquare.wrap>

  return m.ptr();

}
