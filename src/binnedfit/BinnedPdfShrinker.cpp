#include <BinnedPdfShrinker.h>
#include <PdfExceptions.h>

BinnedPdfShrinker::BinnedPdfShrinker(unsigned nDims_){
    fLowerBinBuffers = std::vector<unsigned>(nDims_, 0);
    fUpperBinBuffers = std::vector<unsigned>(nDims_, 0);
    fUsingOverflows  = true; // move into overflow by default, if true just throw away the buffer bins
    fNDims = nDims_;
}


void
BinnedPdfShrinker::SetLowerBuffer(size_t dimension_, unsigned nBins_){
    if (dimension_ >= fNDims)
        throw DimensionError("BinnedPdfShrinker::Tried to set lower buffer on non-existent dimension");
    fLowerBinBuffers[dimension_] = nBins_;
}


void
BinnedPdfShrinker::SetUpperBuffer(size_t dimension_, unsigned nBins_){
    if (dimension_ >= fNDims)
        throw DimensionError("BinnedPdfShrinker::Tried to set upper buffer on non-existent dimension");
    fUpperBinBuffers[dimension_] = nBins_;
}


unsigned
BinnedPdfShrinker::GetUpperBuffer(size_t dimension_) const{
    try{
        return fUpperBinBuffers.at(dimension_);
    }

    catch(const std::out_of_range&){
        throw DimensionError("BinnedPdfShrinker::Attempted access on non-existent fit dimension");
    }

}

unsigned
BinnedPdfShrinker::GetLowerBuffer(size_t dimension_) const{
    try{
        return fLowerBinBuffers.at(dimension_);
    }

    catch(const std::out_of_range&){
        throw DimensionError("BinnedPdfShrinker::Attempted access on non-existent fit dimension");
    }

}


size_t
BinnedPdfShrinker::GetNDims() const{
    return fLowerBinBuffers.size();
}

PdfAxis
BinnedPdfShrinker::ShrinkAxis(const PdfAxis& axis_, const unsigned lowerBuff_, 
                              const unsigned upperBuff_) {
    // no buffer no problem
    if (!lowerBuff_ && !upperBuff_)
        return axis_;

    if (lowerBuff_ > axis_.GetNBins() || upperBuff_ > axis_.GetNBins())
        throw BinError("BinnedPdfShrinker::Buffersize exceeds number of bins!");
    
    const size_t oldBinCount = axis_.GetNBins();
    const size_t newBinCount = oldBinCount - upperBuff_ - lowerBuff_;

    std::vector<double> lowEdges(newBinCount, 0);
    std::vector<double> highEdges(newBinCount, 0);

    // fill the vectors of the new edges using a simple offset
    for(size_t i = 0; i < newBinCount; i++){
        size_t equivilentOldBin = lowerBuff_ + i;
        lowEdges[i]   = axis_.GetBinLowEdge(equivilentOldBin);
        highEdges[i]  = axis_.GetBinHighEdge(equivilentOldBin);
    }

    return PdfAxis(axis_.GetName(), lowEdges, highEdges, axis_.GetLatexName());
}

BinnedPdf
BinnedPdfShrinker::ShrinkPdf(const BinnedPdf& pdf_) const{
    // 1. Build new axes. ShrinkPdf method just makes a copy if buffer size is zero
    AxisCollection newAxes;
    const std::vector<size_t> pdfDataIndicies = pdf_.GetDataRep().GetIndicies();
    unsigned bufferLow  = 0;
    unsigned bufferHigh = 0;
    size_t nDims = pdf_.GetNDims();

    for(size_t i = 0; i < nDims; i++){
        bufferLow  = fLowerBinBuffers.at(pdfDataIndicies.at(i));
        bufferHigh = fUpperBinBuffers.at(pdfDataIndicies.at(i));
        newAxes.AddAxis(ShrinkAxis(pdf_.GetAxes().GetAxis(i), bufferLow, bufferHigh));
    }
        

    // 2. Initialise the new pdf with same data rep
    BinnedPdf newPdf(newAxes);
    newPdf.SetDataRep(pdf_.GetDataRep());

    // 3. Fill the axes
    std::vector<size_t> newIndicies(pdf_.GetNDims()); 
    int   offsetIndex = 0; // note taking difference of two unsigneds
    size_t newBin = 0;

    const AxisCollection& axes = pdf_.GetAxes();

    // bin by bin of old pdf
    for(size_t i = 0; i < pdf_.GetNBins(); i++){
        // work out the index of this bin in the new shrunk pdf. 
        for(size_t j = 0; j < nDims; j++){
            offsetIndex = axes.UnflattenIndex(j, i) - fLowerBinBuffers.at(j);

            // Correct the ones that fall in the buffer regions
            // bins in the lower buffer have negative index. Put in first bin in fit region or ignore
            if (offsetIndex < 0){
                if (fUsingOverflows)
                    offsetIndex = fLowerBinBuffers.at(j);
                else
                    break;
            }
            // bins in the upper buffer have i > number of bins in axis j. Do the same
            if (offsetIndex > axes.GetAxis(j).GetNBins()){
                if (fUsingOverflows)
                    offsetIndex = fUpperBinBuffers.at(j);
                else
                    break;
            }
            
            newIndicies[j] = offsetIndex;
        }
        // Fill 
        newBin = newAxes.FlattenIndicies(newIndicies);
        newPdf.SetBinContent(newBin, pdf_.GetBinContent(i));
    }

    newPdf.Normalise();
    return newPdf;
}

