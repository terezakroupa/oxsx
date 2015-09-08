/******************************************************/
/* A class to read ROOT NTuples and hand out the data */
/******************************************************/

#ifndef __ROOT_HANDLE__
#define __ROOT_HANDLE__
#include <string>
#include <TNtuple.h>
#include <TFile.h>

class DataHandler;
class ROOTHandle {
 public:
    ROOTHandle(const std::string& fileName_, const std::string& treeName_);
    ~ROOTHandle();

    DataHandler Next();
    DataHandler First();
    DataHandler Last();
    DataHandler GetEntry(size_t iEvent_);
    unsigned    GetNEntries() const {return fNEntries;}
    
 private:
    unsigned fIter;
    unsigned fNVar;
    unsigned fNEntries;
    TFile*   fROOTFile;
    TNtuple* fNtuple;
    
    DataHandler Assemble(size_t iEvent_) const;
};

class ROOTError : public std::runtime_error {
 public:
 ROOTError(const std::string& error_str):runtime_error(error_str){};
};



#endif
