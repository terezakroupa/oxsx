#include <BinnedPdfManager.h>
#include <SystematicManager.h>
#include <BinnedPdf.h>
#include <iostream>
#include <PdfExceptions.h>

unsigned 
BinnedPdfManager::GetNPdfs() const{
    return fOriginalPdfs.size();
}

size_t
BinnedPdfManager::GetNDims() const{
    return fNDims;
}

double 
BinnedPdfManager::Probability(const EventData& data_) const{
    double sum = 0;

    for(size_t i = 0; i < fWorkingPdfs.size(); i++){
        sum += fNormalisations.at(i) * fWorkingPdfs[i].Probability(data_);
    }

    return sum;
}

double
BinnedPdfManager::BinProbability(size_t bin_) const{
    double sum = 0;

    try{
        for(size_t i = 0; i < fWorkingPdfs.size(); i++){
            sum += fNormalisations.at(i) * fWorkingPdfs.at(i).GetBinContent(bin_);
        }
    }

    catch(const std::out_of_range&){
        throw DimensionError("BinnedPdfManager:: Normalisation vector doesn't match pdf vector - are the normalisations set?");
    }

    return sum;
}


void
BinnedPdfManager::SetNormalisations(const std::vector<double>& normalisations_){
    if (normalisations_.size() != fOriginalPdfs.size())
        throw DimensionError("BinnedPdfManager: number of norms doesn't match #pdfs");
    fNormalisations = normalisations_;
}

void 
BinnedPdfManager::ApplySystematics(const SystematicManager& sysMan_){
    const std::vector<Systematic*>& systematics = sysMan_.GetSystematics();

    // If there are no systematics or they haven't changed, dont transform the working pdfs 
    //  ( = original pdfs from initialisagtion)
    if((!systematics.size()) || sysMan_.GetParameters() == fCachedParams)
        return;
    fCachedParams = sysMan_.GetParameters();


    for(size_t i = 0; i < systematics.size(); i++)
        for(size_t j = 0; j < fOriginalPdfs.size(); j++)
            fWorkingPdfs[j] = systematics.at(i)->operator()(fOriginalPdfs[j]);
}

const BinnedPdf&
BinnedPdfManager::GetOriginalPdf(size_t index_) const{
    return fOriginalPdfs.at(index_);
}

void
BinnedPdfManager::AddPdf(const BinnedPdf& pdf_){
    fOriginalPdfs.push_back(pdf_);
    fWorkingPdfs.push_back(pdf_);
}

void 
BinnedPdfManager::AddPdfs(const std::vector<BinnedPdf>& pdfs_){
    for(size_t i = 0; i < pdfs_.size(); i++){
        fOriginalPdfs.push_back(pdfs_.at(i));
        fWorkingPdfs.push_back(pdfs_.at(i));
    }
}

const std::vector<double>&
BinnedPdfManager::GetNormalisations() const{
    return fNormalisations;
}
