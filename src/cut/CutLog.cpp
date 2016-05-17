#include <CutLog.h>
#include <Exceptions.h>
#include <iostream>
#include <iomanip>

void
CutLog::CalculateMeta(){
    fRemainderCounts.clear();
    fRemainderPercentages.clear();
    fCutPercentages.clear();

    fRemainderCounts.reserve(fCutCounts.size());
    fRemainderPercentages.reserve(fCutCounts.size());
    fCutPercentages.reserve(fCutCounts.size());
    
    int numRemaining = fNEvents;
    for(size_t i = 0; i < fCutCounts.size(); i++){
        numRemaining -= fCutCounts.at(i);
        fRemainderCounts.push_back(numRemaining);

        fCutPercentages.push_back(fCutCounts.at(i) * 100./fNEvents);
        fRemainderPercentages.push_back(numRemaining * 100./fNEvents);
    }
}

void 
CutLog::LogPass(){
    fNEvents++;
}

void
CutLog::LogCut(size_t index_){
    if(index_ >= fCutCounts.size())
        throw NotFoundError(Formatter() << "CutLog::LogCut tried to log event as cut by non-existent cut #" << index_ );
    fCutCounts[index_]++;
    fNEvents++;
}

std::vector<int>
CutLog::GetCutCounts() const{
    return fCutCounts;
}

std::vector<double>
CutLog::GetCutPercentages() const{   
    return fCutPercentages;
}

std::vector<std::string>
CutLog::GetCutNames() const{
    return fCutNames;
}

std::string
CutLog::AsString() const{
    if (fCutCounts.size() != fCutNames.size())
        throw LogicError(Formatter() << "CutLog::AsString() there are " 
                         << fCutCounts.size() 
                         << " cut counts and " 
                         << fCutNames.size() << " names!");
    Formatter outString;
    outString << "#s cut:\n";
    for(size_t i = 0; i < fCutNames.size(); i++)
        outString << std::left
                  << std::setw(17)
                  << fCutNames.at(i)  << "\t" 
                  << std::left
                  << std::setw(17)
                  << fCutCounts.at(i) << "\t"
                  << std::left
                  << std::setw(1)
                  << "(" << fCutPercentages.at(i) << "%)"
                  << "\n";

    outString << "\n#s remaining after cut:\n";
    outString << std::setw(17) << std::left << "Total event count\t" << fNEvents << "\n";
    for(size_t i = 0; i < fCutNames.size(); i++)
        outString << std::setw(17)
                  << std::left 
                  << fCutNames.at(i)  << "\t" 
                  << std::setw(17)
                  << std::left
                  << fRemainderCounts.at(i) << "\t"
                  << std::left
                  << std::setw(1)
                  << "(" << fRemainderPercentages.at(i) << "%)"
                  << "\n";

    return outString;
}

void
CutLog::Print() const{
    std::cout << AsString() << std::endl;
}
