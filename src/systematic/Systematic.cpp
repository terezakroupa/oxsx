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
Systematic::SetPdfDataRep(const DataRepresentation& rep_) {fPdfDataRep = rep_;}

DataRepresentation
Systematic::GetPdfDataRep() const {return fPdfDataRep;}

void
Systematic::SetParameters(const std::vector<double>& params_) {fParams = params_;}

const std::vector<double>& 
Systematic::GetParameters() const {return fParams;}

size_t
Systematic::GetParamCount() const {return fParams.size();}


bool
Systematic::BinsCompatible(size_t bin1, size_t bin2) const{
    // unpack
    std::vector<size_t> bin1Indicies = fPdfMapping.GetAxes().UnpackIndicies(bin1);
    std::vector<size_t> bin2Indicies = fPdfMapping.GetAxes().UnpackIndicies(bin2);

    std::vector<size_t> relativeIndices = fPdfDataRep.GetRelativeIndicies(fDataRep);
    // Do the two global bin numbers have the same indicies in the dimisensions this systematic affects?
    for(size_t i = 0; i < relativeIndices.size(); i++){
        if (bin1Indicies.at(i) != bin2Indicies.at(i))
            return false;
    }
        
    return true;
}

