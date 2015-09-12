
#include <Systematic.h>

BinnedPdf Systematic::operator() (const BinnedPdf& pdf_) const{
    return fPdfMapping(pdf_, fDataRep.GetIndicies());
}

void Systematic::SetResponse(const std::vector<std::vector<double> >& responseMatrix_){
    fPdfMapping.SetResponse(responseMatrix_);
}

const PdfMapping& Systematic::GetResponse() const{
    return fPdfMapping;
}

void
Systematic::SetDataRep(const DataRepresentation& rep_) {fDataRep = rep_;}

DataRepresentation
Systematic::GetDataRep() const {return fDataRep;}

void
Systematic::SetParameters(const std::vector<double>& params_) {fParams = params_;}

const std::vector<double>& 
Systematic::GetParameters() const {return fParams;}

size_t
Systematic::GetParamCount() const {return fParams.size();}
