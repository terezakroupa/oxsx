#include <PdfManager.h>
#include <Pdf.h>
#include <EventData.h>

PdfManager::~PdfManager(){
    for(size_t i = 0; i < fPdfs.size(); i++)
        delete fPdfs[i];
}

void 
PdfManager::AddPdf(Pdf * pdf_){
    fPdfs.push_back(pdf_->Clone());
    fNPdfs++;
    fNormalisations.resize(fNPdfs, 0);
}

void
PdfManager::AddPdfs(const std::vector<Pdf*>& pdfs_){
    for(size_t i = 0; i < pdfs_.size(); i++)
        AddPdf(pdfs_.at(i));
}

double
PdfManager::Probability(const EventData& event_) const{
    double prob = 0;
    for(size_t i = 0; i < fPdfs.size(); i++)
        prob += fNormalisations.at(i) * fPdfs.at(i)->Probability(event_);
    return prob;
}

const std::vector<double>&
PdfManager::GetNormalisations() const{
    return fNormalisations;
}

void
PdfManager::SetNormalisations(const std::vector<double>& norms_){
    if (norms_.size() != fNPdfs)
        throw 0;
    fNormalisations = norms_;
}


// Make a fittable component - i.e. rescale pdfs inside to fit
void
PdfManager::MakeFittable(){
    EmptyParameters();
    fNormalisations.resize(fNPdfs);
    AddContainerOfParameters<std::vector<double> >(fNormalisations, 
                                                   "Pdf Normalisation");
}
