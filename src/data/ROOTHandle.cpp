#include <ROOTHandle.h>
#include <EventData.h>
#include <iostream>

ROOTHandle::ROOTHandle(const std::string& fileName_, const std::string& treeName_){
    // FIXME -- needs excpetions for failing to get the tree
    fROOTFile = new TFile(fileName_.c_str());
    if (fROOTFile->IsZombie()){
        delete fROOTFile;
        throw ROOTError("ROOTHandle::File Does not Exist! or is Zombie " + fileName_);
    }
        
    fNtuple = static_cast<TNtuple*>(fROOTFile -> Get(treeName_.c_str()));
    if(!fNtuple){
        delete fROOTFile;
        throw ROOTError("ROOTHandle::Tree Does not Exist! " + treeName_);
    }        

    fNEntries = fNtuple -> GetEntries();
    fIter = 0;
    fNVar = fNtuple -> GetNvar();
}

ROOTHandle::~ROOTHandle(){
    if (fROOTFile)
        fROOTFile -> Close();
    delete fROOTFile;
}

EventData 
ROOTHandle::Assemble(size_t iEvent_) const{
    fNtuple -> GetEntry(iEvent_);
    float* vals = fNtuple -> GetArgs();
    return EventData(std::vector<double> (vals, vals + fNVar));
    
}

EventData
ROOTHandle::GetEntry(size_t iEvent_){
    if(fIter > fNEntries)
        throw 0; //fix me
    fIter = iEvent_;
    return Assemble(fIter);
}


EventData 
ROOTHandle::First(){
    fIter = 0;
    return Assemble(fIter);
}

EventData 
ROOTHandle::Next(){
    if(fIter == (fNEntries -1))
        throw 0; // handle this case betxter something better
    return Assemble(++fIter);
}

EventData 
ROOTHandle::Last(){
    fIter = fNEntries -1; 
    return Assemble(fIter);
}
