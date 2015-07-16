#include "Event.h"
#include "../pdf/Pdf.h"
#include <iostream>


Event::Event(const std::vector<const Pdf*>& pdfs_,
             const std::vector<std::vector<size_t> >& indicies_,
             const std::string& name_, const std::string& latexName_){
    fName = name_;
    fLatexName = latexName_;
    fPDFs = pdfs_;
    
    if(pdfs_.size() == 1)
        fOnePdf = true;
    else
        fOnePdf = false;    
}

Event::Event(const Pdf* pdf_,
             const std::string& name_, const std::string& latexName_){
    fName = name_;
    fLatexName = latexName_;
    fPDFs = std::vector<const Pdf*>(1,pdf_);
    
    fOnePdf = true;

}

double Event::MultiPdfProbability(const std::vector<double>* vals_) const{
    double prob = 1;
    for(size_t i = 0; i < vals_->size(); i++)
        prob *= fPDFs[i] -> operator()(vals_, fIndicies[i]);
    return prob;
}

double Event::OnePdfProbability(const std::vector<double>* vals_) const{
    return fPDFs[0] -> operator()(vals_);
}

double Event::Probability(const std::vector<double>* vals_) const{
    if (fOnePdf)
        return OnePdfProbability(vals_);
    return MultiPdfProbability(vals_);
}
