#include <Systematic.h>
#include <PdfExceptions.h>
#include <algorithm>
#include <iostream>

BinnedPdf 
Systematic::operator() (const BinnedPdf& pdf_) const{
    BinnedPdf afterSmear = fPdfMapping(pdf_);
    afterSmear.Normalise();
    return afterSmear;
}

void 
Systematic::SetResponse(const PdfMapping& responseMatrix_){
    fPdfMapping = responseMatrix_;
}

const PdfMapping& 
Systematic::GetResponse() const{
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
Systematic::SetParameters(const std::vector<double>& params_) {
    fParams = params_;
}

std::vector<double>
Systematic::GetParameters() const {return fParams;}

// use this, so that you get the derived class method
// e.g. in the convolution you want to know the number of parameters in the underlying pdf
size_t
Systematic::GetParamCount() const {return this->GetParameters().size();}


bool
Systematic::BinsCompatible(size_t bin1_, size_t bin2_) const{
    std::vector<size_t> bin1Indices = fPdfMapping.GetAxes().UnpackIndices(bin1_);
    std::vector<size_t> bin2Indices = fPdfMapping.GetAxes().UnpackIndices(bin2_);

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

double
Systematic::GetParameter(size_t index_) const {
    try{
        return fParams.at(index_);
    }
    catch (const std::out_of_range& e){
        throw OutOfBoundsError("Systematic::GetParameter, parameter of t\
hat index doesn't exist!");
    }
}

void
Systematic::SetParameter(size_t index_, double val_){
    try{
        fParams[index_] = val_;
    }  
    catch (const std::out_of_range& e){
        throw OutOfBoundsError("Systematic::SetParameter, parameter of hat index doesn't exist!");
    }
}

