#include <Convolution.h>
#include <IntegrablePdf.h>

void Convolution::SetPdf(IntegrablePdf* pdf_){
    fPdf = dynamic_cast<IntegrablePdf*>(pdf_->Clone());
    if(!fPdf)
        throw 0; //FIXME not an integrable pdf
}

Convolution::~Convolution(){
    delete fPdf;
}

void Convolution::SetAxes(const AxisCollection& axes_){
    fPdfMapping.SetAxes(axes_);
    Construct();
}

void Convolution::Construct(){
    if (!fPdf)
        return;

    size_t nBins = fPdfMapping.GetNBins();
    for(size_t i = 0; i < nBins; i++){
        std::vector<double> binCentre = fPdfMapping.GetAxes().GetBinCentre(i);

        // Integrate over bin j to work out the response from i -> j
        for(size_t j = 0; j < nBins; j++){
            std::vector<double> lowEdges  = fPdfMapping.GetAxes().GetBinLowEdges(j);
            std::vector<double> highEdges = fPdfMapping.GetAxes().GetBinHighEdges(j);

            // Move the pdf origin to the centre of bin i
            for(size_t k = 0; k < lowEdges.size(); k++){
                lowEdges[k]  = binCentre[k] - lowEdges[k];
                highEdges[k] = binCentre[k] - highEdges[k];
            }
            double Rij = fPdf -> Integral(highEdges, lowEdges);
            fPdfMapping.SetComponent(i, j, Rij);
        }
    }        
}
