#include <Convolution.h>
#include <IntegrablePdf.h>
#include <iostream>

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
}

void Convolution::Construct(){
    if (!fPdf)
        return;

    Reset();
    size_t nBins = fPdfMapping.GetNBins();
    
    for(size_t i = 0; i < nBins; i++){
        std::vector<double> binCentre = fPdfMapping.GetAxes().GetBinCentre(i);

        // Integrate over bin j to work out the response from i -> j
        for(size_t j = 0; j < nBins; j++){
            // only smear if the systematic indicies are the same in both bins
            // others remain zero from intialistion
            if(!BinsCompatible(i,j))
                continue;

            std::vector<double> lowEdges  = fPdfMapping.GetAxes().GetBinLowEdges(j);
            std::vector<double> highEdges = fPdfMapping.GetAxes().GetBinHighEdges(j);

            // Move the pdf origin to the centre of bin i
            for(size_t k = 0; k < lowEdges.size(); k++){
                lowEdges[k]  -=  binCentre[k];
                highEdges[k] -=  binCentre[k];
            }

            double Rij = fPdf -> Integral(lowEdges, highEdges);
            fPdfMapping.SetComponent(j, i, Rij);
        }
    }        

    std::cout << "inside convolution, sigma = " << fPdf->GetParameter(1) << "\t" << std::endl;
}

void
Convolution::SetParameters(const std::vector<double>& params_){
    fPdf->SetParameters(params_);
}

std::vector<double>
Convolution::GetParameters() const{
    return fPdf->GetParameters();
}

double 
Convolution::GetParameter(size_t index_) const{
    return fPdf->GetParameter(index_);
}

void
Convolution::SetParameter(size_t index_, double val_){
    fPdf->SetParameter(index_, val_);
}

void
Convolution::Reset(){
    for(size_t i = 0; i < fPdfMapping.GetNBins(); i++)
        for(size_t j = 0; j < fPdfMapping.GetNBins(); j++)
            fPdfMapping.SetComponent(i, j , 0);
}
