#include <ROOTHandle.h>
#include <DataHandler.h>
#include <iostream>

ROOTHandle::ROOTHandle(const std::string& fileName_, const std::string& treeName_){
    // FIXME -- needs excpetions for failing to get the tree
    fROOTFile = new TFile(fileName_.c_str());
    fNtuple = static_cast<TNtuple*>(fROOTFile -> Get(treeName_.c_str()));
    fNEntries = fNtuple -> GetEntries();
    fIter = 0;
    fNVar = fNtuple -> GetNvar();
}

ROOTHandle::~ROOTHandle(){
    if (fROOTFile)
        fROOTFile -> Close();
    delete fROOTFile;
}

DataHandler ROOTHandle::Assemble(size_t iEvent_) const{
    fNtuple -> GetEntry(iEvent_);
    float* vals = fNtuple -> GetArgs();
    return DataHandler(std::vector<double> (vals, vals + fNVar));
    
}

DataHandler ROOTHandle::First(){
    fIter = 0;
    return Assemble(fIter);
}

DataHandler ROOTHandle::Next(){
    if(fIter == (fNEntries -1))
        throw 0; // handle this case betxter something better
    return Assemble(++fIter);
}

DataHandler ROOTHandle::Last(){
    fIter = fNEntries -1; 
    return Assemble(fIter);
}
