#include <PdfCollection.h>
#include <Systematic.h>
PdfCollection::~PdfCollection(){
    for(size_t i = 0; i < fPdfs.size(); i++)
        delete fPdfs[i];
}

size_t
PdfCollection::GetNDims() const{
    return fNDims;
}

double 
PdfCollection::Probability(const DataHandler& data_) const{
    double sum = 0;
    for(size_t i = 0; i < fPdfs.size(); i++)
        sum += fNormalisations[i] * fPdfs[i]->operator()(data_);
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
            fPdfs[j] = systematics_.at(i).operator()(fPdfs[j]);
    }
}
