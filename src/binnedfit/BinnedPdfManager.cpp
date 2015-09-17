#include <BinnedPdfManager.h>
#include <Systematic.h>
#include <BinnedPdf.h>

size_t
BinnedPdfManager::GetNDims() const{
    return fNDims;
}

double 
BinnedPdfManager::Probability(const EventData& data_) const{
    double sum = 0;
    for(size_t i = 0; i < fWorkingPdfs.size(); i++)
        sum += fNormalisations[i] * fWorkingPdfs[i].Probability(data_);
    return sum;
}

void
BinnedPdfManager::SetNormalisations(const std::vector<double>& normalisations_){
    fNormalisations = normalisations_;
}

void 
BinnedPdfManager::ApplySystematics(const std::vector<Systematic>& systematics_){
    for(size_t i = 0; i < systematics_.size(); i++){
        for(size_t j = 0; j < systematics_.size(); j++)
            fWorkingPdfs[j] = systematics_.at(i).operator()(fOriginalPdfs[j]);
    }
}

const BinnedPdf&
BinnedPdfManager::GetOriginalPdf(size_t index_) const{
    return fOriginalPdfs.at(index_);
}

void
BinnedPdfManager::AddPdf(const BinnedPdf& pdf_){
    fOriginalPdfs.push_back(pdf_);
}

void 
BinnedPdfManager::AddPdfs(const std::vector<BinnedPdf>& pdfs_){
    for(size_t i = 0; i < pdfs_.size(); i++)
        fOriginalPdfs.push_back(pdfs_.at(i));
}
