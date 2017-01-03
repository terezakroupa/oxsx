#ifndef __OXSX_PARAMETER_MANAGER__
#define __OXSX_PARAMETER_MANAGER__
#include <vector>
#include <string>
#include <iostream>
class FitParameter;
class ParameterManager{
 public:
    ParameterManager() {}
    ~ParameterManager(); // frees fParamPtrs

    // don't copy the other objects parameter pointers, it has its own
    ParameterManager(const ParameterManager&) {}
    ParameterManager operator=(const ParameterManager&) {return ParameterManager();}

    // Add parameters
    void Add(FitParameter*, const std::string&); // copies 
    void AddDouble(double&, const std::string&);
    template<typename Container>        
    void AddContainer(Container&,
                      const std::string& nameBase_);
    template<typename Container>        
    void AddContainer(Container&,
                      const std::vector<std::string>& names_);
    void Clear();

    // Used to implement FitComponent interface
    std::vector<std::string> GetParameterNames() const;
    void SetParameterNames(const std::vector<std::string>&);


    std::vector<double> GetParameters() const;
    void SetParameters(const std::vector<double>&);

    size_t GetParameterCount() const;
 private:
    std::vector<FitParameter*> fParamPtrs;
    std::vector<std::string>   fNames;
};

// implements AddContainerOfParameters(-)
#include <ParameterManager.hpp> 
#endif
