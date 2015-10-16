#include <BinnedPdfShrinker.h>
#include <PdfExceptions.h>
#include <DataExceptions.h>
#include <iostream>

BinnedPdfShrinker::BinnedPdfShrinker(unsigned nDims_){
    fLowerBinBuffers = std::vector<unsigned>(nDims_, 0);
    fUpperBinBuffers = std::vector<unsigned>(nDims_, 0);
    fUsingOverflows  = true; // move into overflow by default, if false just throw away the buffer bins
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

    if (nDims != fNDims)
        throw DimensionError("BinnedPdfShrinker:: Pdf Dimensionality doesn't match shrinker");

    if(pdfDataIndicies.size() != fNDims)
        throw RepresentationError("BinnedPdfShrinker:: Input pdf data rep doesnt match dimensionality of pdf - which indicies do I shrink?");

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
    double content = 0;
    // bin by bin of old pdf
    for(size_t i = 0; i < pdf_.GetNBins(); i++){
        content = pdf_.GetBinContent(i);
        // work out the index of this bin in the new shrunk pdf. 
        for(size_t j = 0; j < nDims; j++){
            offsetIndex = axes.UnflattenIndex(i, j) - fLowerBinBuffers.at(j);

            // Correct the ones that fall in the buffer regions
            // bins in the lower buffer have negative index. Put in first bin in fit region or ignore
            if (offsetIndex < 0){
                offsetIndex = 0;
                if(!fUsingOverflows)
                    content = 0;

            }
            // bins in the upper buffer have i > number of bins in axis j. Do the same
            if (offsetIndex >= newAxes.GetAxis(j).GetNBins()){
                offsetIndex = newAxes.GetAxis(j).GetNBins() - 1;
                if (!fUsingOverflows)
                    content = 0;
            }

            newIndicies[j] = offsetIndex;
        }
        // Fill 
        newBin = newAxes.FlattenIndicies(newIndicies);
        newPdf.AddBinContent(newBin, content);
    }
    return newPdf;
}

void
BinnedPdfShrinker::SetUsingOverflows(bool b_){
    fUsingOverflows = b_;
}

bool
BinnedPdfShrinker::GetUsingOverflows() const{
    return fUsingOverflows;
}
