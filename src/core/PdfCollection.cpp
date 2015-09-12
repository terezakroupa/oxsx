#include <PdfCollection.h>
#include <Systematic.h>
#include <BinnedPdf.h>

size_t
PdfCollection::GetNDims() const{
    return fNDims;
}

double 
PdfCollection::Probability(const DataHandler& data_) const{
    double sum = 0;
    for(size_t i = 0; i < fWorkingPdfs.size(); i++)
        sum += fNormalisations[i] * fWorkingPdfs[i].Probability(data_);
    return sum;
}

void
PdfCollection::SetNormalisations(const std::vector<double>& normalisations_){
    fNormalisations = normalisations_;
}

void 
PdfCollection::ApplySystematics(const std::vector<Systematic>& systematics_){
    for(size_t i = 0; i < systematics_.size(); i++){
        for(size_t j = 0; j < systematics_.size(); j++)
            fWorkingPdfs[j] = systematics_.at(i).operator()(fOriginalPdfs[j]);
    }
}

