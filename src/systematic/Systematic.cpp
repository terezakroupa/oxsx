#include <Systematic.h>

BinnedPdf Systematic::operator() (const BinnedPdf& pdf_, const std::vector<size_t>& indicies_) const{
    return fResponseMatrix(pdf_, indicies_);
}

void Systematic::SetResponse(const std::vector<std::vector<double> >& responseMatrix_){
    fResponseMatrix.SetResponse(responseMatrix_);
}

const ResponseMatrix& Systematic::GetResponse() const{
    return fResponseMatrix;
}
