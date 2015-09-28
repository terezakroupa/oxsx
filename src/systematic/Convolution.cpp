#include <Convolution.h>
#include <IntegrablePdf.h>
#include <iostream>
#include <PdfExceptions.h>
#include <SystematicExceptions.h>

// Catch the pdf errors from parameter setting and rethrow as systematic exceptions, so they
// can be treated generically with the other systematics

void Convolution::SetPdf(IntegrablePdf* pdf_){
    fPdf = dynamic_cast<IntegrablePdf*>(pdf_->Clone());
    fParameterCount = fPdf->GetParameters().size();
    if(!fPdf)
        throw InitialisationError("Non-Integrable pdf used for convolution!");
}

Convolution::~Convolution(){
    delete fPdf;
}

void Convolution::SetAxes(const AxisCollection& axes_){
    fPdfMapping.SetAxes(axes_);
    fHasAxes = true;
}

void Convolution::Construct(){
    if (!fPdf || !fHasAxes)
        throw InitialisationError("Tried to construct convolution without axes and pdf!");
    
    if(!fCachedCompatibleBins)
        CacheCompatibleBins();

    Reset();
    size_t nBins = fPdfMapping.GetNBins();
    size_t nDims = fPdfMapping.GetAxes().GetNDimensions();
    const AxisCollection& axes = fPdfMapping.GetAxes();
    std::vector<size_t> relativeIndicies = fDataRep.GetRelativeIndicies(fPdfDataRep);

    std::vector<double> binCentre(relativeIndicies.size());
    std::vector<double> lowEdges(relativeIndicies.size());
    std::vector<double> highEdges(relativeIndicies.size());

    for(size_t i = 0; i < nBins; i++){
        for(size_t k = 0; k < relativeIndicies.size(); k++)
            binCentre[k] = axes.GetBinCentre(i, relativeIndicies.at(k));

        // Loop over compatible bins and integrate over bin j to work out the response from i -> j
        // others are zero from reset
        for(size_t j = 0; j < fCompatibleBins.at(i).size(); j++){
            size_t mappedBin = fCompatibleBins.at(i).at(j);
            
            for(size_t k = 0; k < relativeIndicies.size(); k++){
                lowEdges[k]  = axes.GetBinLowEdge(mappedBin, relativeIndicies.at(k));
                highEdges[k] = axes.GetBinHighEdge(mappedBin, relativeIndicies.at(k));
                
            }

            // Move the pdf origin to the centre of bin i
            for(size_t k = 0; k < lowEdges.size(); k++){
                lowEdges[k]  -=  binCentre[k];
                highEdges[k] -=  binCentre[k];
            }

            double Rij = fPdf -> Integral(lowEdges, highEdges);
            fPdfMapping.SetComponent(mappedBin, i, Rij);
        }
    }        
}

void
Convolution::SetParameters(const std::vector<double>& params_){
    try{
    fPdf->SetParameters(params_);
    }
    catch (const ParameterError& e_){
        throw InvalidSystematicParameter(std::string("Convolution: couldnt set pdf params, invalid val:  ") + e_.what());
    }
    catch (const DimensionError& e_){
        throw WrongNumberOfParameters(std::string("Convolution: tried to change pdf params with wrong number") + e_.what());
    }

}

std::vector<double>
Convolution::GetParameters() const{
    return fPdf->GetParameters();
}

double 
Convolution::GetParameter(size_t index_) const{
    try{
        return fPdf->GetParameter(index_);
    }
    catch(const DimensionError& e_){
        throw WrongNumberOfParameters("Convolution: Tried to access a variable the pdf does not have!");
    }
}

void
Convolution::SetParameter(size_t index_, double val_){
    try{
        fPdf->SetParameter(index_, val_);
    }
    catch(const DimensionError& e_){
        throw WrongNumberOfParameters("Convolution: Tried to access a variable the pdf does not have!");       
    }
}

void
Convolution::Reset(){
    for(size_t i = 0; i < fPdfMapping.GetNBins(); i++)
        for(size_t j = 0; j < fPdfMapping.GetNBins(); j++)
            fPdfMapping.SetComponent(i, j , 0);
}

void
Convolution::CacheCompatibleBins(){
    fCompatibleBins.resize(fPdfMapping.GetNBins());
    // only need to look at one side of the matrix, its symmetric
    for(size_t i = 0; i < fPdfMapping.GetNBins(); i++){
        for(size_t j = i;  j < fPdfMapping.GetNBins(); j++){
            fCompatibleBins.at(i).push_back(j);
            fCompatibleBins.at(j).push_back(i);
        }
    }
    fCachedCompatibleBins = true;
}
