
#include <Systematic.h>

BinnedPdf Systematic::operator() (const BinnedPdf& pdf_, const std::vector<size_t>& indicies_) const{
    return fPdfMapping(pdf_, indicies_);
}

void Systematic::SetResponse(const std::vector<std::vector<double> >& responseMatrix_){
    fPdfMapping.SetResponse(responseMatrix_);
}

const PdfMapping& Systematic::GetResponse() const{
    return fPdfMapping;
}
