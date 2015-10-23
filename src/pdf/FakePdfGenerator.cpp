#include <FakePdfGenerator.h>
#include <PdfExceptions.h>
#include <stdlib.h>
#include <Rand.h>
#include <cmath>
#include <iostream>
#include <algorithm>

BinnedPdf
FakePdfGenerator::ExpectedRatesPdf() const{
    if(!(fPdfs.size() == fRates.size()))
        throw DimensionError("FakePdfGenerator::Need exactly one rate for each ");
   
    if (!fPdfs.size())
        throw DimensionError("FakePdfGenerator::No source pdfs!!");

    BinnedPdf fakePdf(fPdfs.at(0));
    fakePdf.Empty();
    for(size_t i = 0; i < fPdfs.size(); i++){
        unsigned counts = round(fRates.at(i));         
        for(unsigned _ = 0; _ < counts; _++)
            fakePdf.AddBinContent(RandomBin(i), 1);
    }
        
    return fakePdf;
}

size_t
FakePdfGenerator::RandomBin(size_t pdfIndex_) const{
    if (!fPdfs.at(pdfIndex_).GetNDims())
        throw DimensionError("FakePdfGenerator::Pdf of dimension 0!");

    // construct cdf
    std::vector<double> cdf(fPdfs.at(pdfIndex_).GetNBins(), 0);
    double sum = 0;
    for(size_t i = 0; i < cdf.size(); i++){
        sum += fPdfs.at(pdfIndex_).GetBinContent(i);
        cdf[i] = sum;
    }

    for(size_t i = 0; i < cdf.size(); i++)
        cdf[i] /= sum;
   
    // random val on unit line
    double rnd = Rand::Uniform();
    return std::lower_bound(cdf.begin(), cdf.end(), rnd) - cdf.begin();
}
