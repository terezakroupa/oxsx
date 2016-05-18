#include <CountingResult.h>
#include <Formatter.hpp>
#include <numeric>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>

void
CountingResult::AddBackground(double expectedRate_, const std::string& name_,
                              const CutLog& log_){
    fExpectedRates.push_back(expectedRate_);
    fBackgroundNames.push_back(name_);
    fBackgroundLogs.push_back(log_);
    fBackgroundLogs.back().CalculateMeta();
}

void
CountingResult::SetDataLog(const CutLog& log_){
    fDataLog = log_;
    fDataLog.CalculateMeta();
}

void
CountingResult::SetObservedCounts(int counts_){
    fObservedCounts = counts_;
}

double
CountingResult::GetExpectedCounts() const{
    return std::accumulate(fExpectedRates.begin(), fExpectedRates.end(),
                           0.);
}

int 
CountingResult::GetObservedCounts() const{
    return fObservedCounts;
}

void 
CountingResult::SetSignal(double sigEff_, const std::string& name_, const CutLog& log_){
    fSignalName = name_;
    fSignalLog  = log_;
    fSignalLog.CalculateMeta();
    fSignalEfficiency = sigEff_;
    
}

void
CountingResult::Print() const{
    std::cout << AsString() << std::endl;
}

void 
CountingResult::SaveAs(const std::string& fileName_) const{
    time_t t = time(0);
    struct tm * now = localtime(&t);

    std::ofstream fs(fileName_.c_str());
    fs << "-----------------------------------"
       << "-----------------------------------" << std::endl
       << "OXSX Counting Result: "
       << now -> tm_year + 1900 << '-' 
       << now -> tm_mon + 1 << '-'
       << now -> tm_mday
       << "  "
       << now -> tm_hour
       << ":"
       << now -> tm_min
       << ":"
       << now -> tm_sec
       << std::endl
       << "-----------------------------------"
       << "-----------------------------------" << std::endl
       << std::endl
       << AsString();       
}
std::string
CountingResult::AsString() const{
    Formatter resultString;
    resultString << "------Backgrounds:----------------------------------------------------\n";
    for(size_t i = 0; i < fBackgroundLogs.size(); i++){
        resultString << "------------------------\n"
                     << fBackgroundNames.at(i) << "\n"
                     << "------------------------\n"
                     << fBackgroundLogs.at(i).AsString()
                     << "\n\n";
        
    }

    resultString << "------Signal----------------------------------------------------------\n";
    resultString << "------------------------\n"
                 << fSignalName << "\n"
                 << "------------------------\n"
                 << fSignalLog.AsString()
                 << "\n\n";
    
    resultString << "------Test:-----------------------------------------------------------\n"
                 << fDataLog.AsString()
                 << "\n\n";
    
    resultString << "------Summary:--------------------------------------------------------\n";
    resultString << "------------------------\n" 
                 << std::left
                 << std::setw(18)
                 << "Background"
                 << std::left
                 << std::setw(10)
                 << "Counts";

    for(size_t i = 0; i < fExpectedRates.size(); i++){
        resultString << "\n"
                     << std::setw(18)
                     << std::left
                     << fBackgroundNames.at(i)
                     << std::setw(10)
                     << std::left
                     << fExpectedRates.at(i)
                     << "\n";
    }
        
    resultString << std::setw(18)
                 << std::left
                 << "Total :" 
                 << std::setw(10)
                 << std::left
                 << GetExpectedCounts()
                 << "\n------------------------\n"
                 << std::setw(18)
                 << std::left
                 << "Signal Efficiency"
                 << std::setw(10)
                 << std::left
                 << fSignalEfficiency
                 << "\n------------------------\n"
                 << std::setw(18)
                 << std::left
                 << "Observed: "
                 << std::setw(10)
                 << std::left
                 << fObservedCounts
                 << "\n"
                 << "----------------------------------------------------------------------\n";
    return resultString;
}
