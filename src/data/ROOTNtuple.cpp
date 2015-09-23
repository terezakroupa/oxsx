#include <ROOTNtuple.h>
#include <EventData.h>
#include <iostream>
#include <DataExceptions.h>

ROOTNtuple::ROOTNtuple(const std::string& fileName_, const std::string& treeName_){
    fROOTFile = new TFile(fileName_.c_str());

    if (fROOTFile->IsZombie()){
        delete fROOTFile;
        throw ROOTError("ROOTNtuple::File Does not Exist! or is Zombie " + fileName_);
    }
        
    fNtuple = static_cast<TNtuple*>(fROOTFile -> Get(treeName_.c_str()));
    if(!fNtuple){
        delete fROOTFile;
        throw ROOTError("ROOTNtuple::Tree Does not Exist! " + treeName_);
    }        

    fNEntries = fNtuple -> GetEntries();
    fIter = 0;
    fNVar = fNtuple -> GetNvar();
}

ROOTNtuple::~ROOTNtuple(){
    if (fROOTFile)
        fROOTFile -> Close();
    delete fROOTFile;
}

EventData 
ROOTNtuple::Assemble(size_t iEvent_) const{
    if (iEvent_ >= fNEntries)
        throw DataNotFoundError("Exceeded end of ROOT NTuple");

    fNtuple -> GetEntry(iEvent_);
    float* vals = fNtuple -> GetArgs();
    return EventData(std::vector<double> (vals, vals + fNVar));
    
}

EventData
ROOTNtuple::GetEntry(size_t iEvent_){
    if(fIter >= fNEntries)
        throw DataNotFoundError("Exceeded end of ROOT NTuple");

    fIter = iEvent_;
    return Assemble(fIter);
}


EventData 
ROOTNtuple::First(){
    fIter = 0;
    return Assemble(fIter);
}

EventData 
ROOTNtuple::Next(){
    if(fIter == (fNEntries -1))
        throw DataNotFoundError("Exceeded end of ROOT NTuple");
    return Assemble(++fIter);
}

EventData 
ROOTNtuple::Last(){
    fIter = fNEntries -1; 
    return Assemble(fIter);
}
