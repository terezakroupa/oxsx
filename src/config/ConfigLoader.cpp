#include <ConfigLoader.hh>
#include <ContainerTools.hpp>
#include <Exceptions.h>
#include <sstream>

INI::Parser* ConfigLoader::fParser = NULL;

void
ConfigLoader::Load(const std::string& section_, const std::string& fieldName_,  std::string& loadVal_){
  loadVal_ = fParser->top()(section_)[fieldName_];
}

void
ConfigLoader::Open(const std::string& fileName_){
    std::ifstream ss;
    ss.open(fileName_.c_str());
    if(!ss){        
        throw IOError("Can't find config file " + fileName_);
    }
    delete fParser;
    fParser = new INI::Parser(ss);
}

void
ConfigLoader::Close(){
    delete fParser;
    fParser = NULL;
}
