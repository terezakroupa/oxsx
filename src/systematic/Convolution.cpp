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

    AxisCollection systematicAxes;
    //  get the axes that this systematic will act on 
    for(size_t i = 0; i < relativeIndicies.size(); i++)
        systematicAxes.AddAxis(axes.GetAxis(relativeIndicies.at(i)));

    // Work out the transition probabilitites within this sub set of the bins
    std::vector<double> binCentres(systematicAxes.GetNDimensions());
    std::vector<double> lowEdges(systematicAxes.GetNDimensions());
    std::vector<double> highEdges(systematicAxes.GetNDimensions());

    PdfMapping subMap;
    subMap.SetAxes(systematicAxes);
    for (size_t origBin = 0; origBin < systematicAxes.GetNBins(); origBin++){
        // get the centre of the bin. Need to offset by this for a convolution
        systematicAxes.GetBinCentres(origBin, binCentres);

        // loop over the bins it can be smeared into 
        for(size_t destBin = 0; destBin < systematicAxes.GetNBins(); destBin++){
            systematicAxes.GetBinLowEdges(destBin, lowEdges);
            systematicAxes.GetBinHighEdges(destBin, highEdges);
            
            for(size_t i = 0; i < systematicAxes.GetNDimensions(); i++){
                lowEdges[i] -= binCentres.at(i);
                highEdges[i] -= binCentres.at(i);
            }

            subMap.SetComponent(destBin, origBin, fPdf -> Integral(lowEdges, highEdges));
        }        
    }

    // Now expand to the full size matrix. Elements are zero by default
    // compatible bins are cached, values must match the smaller matrix above
    std::vector<size_t> origSysInds(relativeIndicies.size());
    std::vector<size_t> destSysInds(relativeIndicies.size());
    
    for(size_t origBin = 0; origBin < axes.GetNBins(); origBin++){
        for(size_t dim =0; dim < relativeIndicies.size(); dim++)
            origSysInds[dim] = axes.UnflattenIndex(origBin, relativeIndicies.at(dim));

        for(size_t destBin = 0; destBin < fCompatibleBins.at(origBin).size(); destBin++){
            for(size_t dim =0; dim < relativeIndicies.size(); dim++)
                destSysInds[dim] = axes.UnflattenIndex(destBin, relativeIndicies.at(dim));
            
            fPdfMapping.SetComponent(destBin, 
                                     origBin, 
                                     subMap.GetComponent(systematicAxes.FlattenIndicies(destSysInds),
                                                         systematicAxes.FlattenIndicies(origSysInds))
                                     );
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
        for(size_t j = i+1;  j < fPdfMapping.GetNBins(); j++){
            fCompatibleBins.at(i).push_back(j);
            fCompatibleBins.at(j).push_back(i);
        }
    }

    fCachedCompatibleBins = true;
}
