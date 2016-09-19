#include <Systematic.h>
#include <Exceptions.h>
#include <algorithm>
#include <iostream>

BinnedED 
Systematic::operator() (const BinnedED& pdf_) const{
    try{
        BinnedED afterSmear = pdf_;
        afterSmear.SetBinContents(fResponse(pdf_.GetBinContents()));
        afterSmear.Normalise();
        return afterSmear;
    }
    catch(const DimensionError& e_){
        throw DimensionError(std::string("Failed to apply systematic :: ") + e_.what());
    }
}

void 
Systematic::SetResponse(const Matrix& responseMatrix_){
    fResponse = responseMatrix_;
}

const Matrix& 
Systematic::GetResponse() const{
    return fResponse;
}

void
Systematic::SetDataRep(const DataRepresentation& rep_) {fDataRep = rep_;}

DataRepresentation
Systematic::GetDataRep() const {return fDataRep;}

void
Systematic::SetPdfDataRep(const DataRepresentation& rep_) {fPdfDataRep = rep_;}

DataRepresentation
Systematic::GetPdfDataRep() const {return fPdfDataRep;}

bool
Systematic::BinsCompatible(size_t bin1_, size_t bin2_) const{
    std::vector<size_t> bin1Indices = fResponse.GetAxes().UnpackIndices(bin1_);
    std::vector<size_t> bin2Indices = fResponse.GetAxes().UnpackIndices(bin2_);

    // Where are the indices the systematic cares about in the pdfs index scheme
    std::vector<size_t> relativeIndices = fDataRep.GetRelativeIndices(fPdfDataRep);

    // Do the two global bin numbers have the same indices except for in the dimisensions 
    // this systematic affects?
    for(size_t i = 0; i < bin1Indices.size(); i++){
        if (VectorContains(relativeIndices, i))
            continue;
        if (bin1Indices.at(i) != bin2Indices.at(i))
            return false;
    }
        
    return true;
}


bool
Systematic::VectorContains(const std::vector<size_t>& vec_,  size_t val_) const{
    return std::find(vec_.begin(), vec_.end(), val_) != vec_.end();
}
