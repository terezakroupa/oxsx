#include "Convolution.h"
#include "../pdf/IntegrablePdf.h"

void Convolution::SetPdf(IntegrablePdf* pdf_){
    fPdf = dynamic_cast<IntegrablePdf*>(pdf_->Clone());
}

Convolution::~Convolution(){
    delete fPdf;
}

void Convolution::SetAxes(const AxisCollection& axes_){
    fResponseMatrix.SetAxes(axes_);
    Construct();
}

void Convolution::Construct(){
    if (!fPdf)
        return;

    size_t nBins = fResponseMatrix.GetNBins();
    for(size_t i = 0; i < nBins; i++){
        std::vector<double> binCentre = fResponseMatrix.GetAxes().GetBinCentre(i);

        // Integrate over bin j to work out the response from i -> j
        for(size_t j = 0; j < nBins; j++){
            std::vector<double> lowEdges  = fResponseMatrix.GetAxes().GetBinLowEdges(j);
            std::vector<double> highEdges = fResponseMatrix.GetAxes().GetBinHighEdges(j);

            // Move the pdf origin to the centre of bin i
            for(size_t k = 0; k < lowEdges.size(); k++){
                lowEdges[k]  = binCentre[k] - lowEdges[k];
                highEdges[k] = binCentre[k] - highEdges[k];
            }
            double Rij = fPdf -> Integral(highEdges, lowEdges);
            fResponseMatrix.SetComponent(i, j, Rij);
        }
    }        
}
