#include <CompositePhysDist.h>
#include <EventData.h>
#include <Exceptions.h>
#include <iostream>

CompositePhysDist::CompositePhysDist(const PhysDist* p1_, const PhysDist* p2_) {
    fDistPtrs.push_back(p1_ -> Clone());
    fDistPtrs.push_back(p2_ -> Clone());  

}

CompositePhysDist::CompositePhysDist(const std::vector<PhysDist*>& pdfs_){
    // if one of the pdfs is composite itself the copy will happen recursively all the way down
    for(size_t i = 0; i < pdfs_.size(); i++){
        fDistPtrs.push_back(pdfs_[i] -> Clone());
    }
}
CompositePhysDist::~CompositePhysDist() {
    for(size_t i = 0; i < fDistPtrs.size(); i++)
        delete fDistPtrs[i];
}

double 
CompositePhysDist::Probability(const EventData& data_) const{
    double prob = 1;
    for(size_t i = 0; i < fDistPtrs.size(); i++)
        prob *= fDistPtrs[i] -> Probability(data_);
    return prob;
}

void 
CompositePhysDist::Normalise(){
    for(size_t i = 0; i < fDistPtrs.size(); i++)
        fDistPtrs[i] -> Normalise();
}

double 
CompositePhysDist::Integral() const{
    double integral = 1;
    for(size_t i = 0; i < fDistPtrs.size(); i++)
        integral *= fDistPtrs[i] -> Integral();
    return integral;
}

PhysDist* 
CompositePhysDist::Clone() const {
    PhysDist *cp = new CompositePhysDist(fDistPtrs);
    return static_cast<PhysDist*>(cp);
}


CompositePhysDist
operator * (const PhysDist& pdf1_, const PhysDist& pdf2_){
    return CompositePhysDist(&pdf1_, &pdf2_);
}


unsigned
CompositePhysDist::GetNDims() const{
    unsigned nDims = 0;
    for(size_t i = 0; i < fDistPtrs.size(); i++)
        nDims += fDistPtrs.at(i)->GetNDims();
    return nDims;
}
