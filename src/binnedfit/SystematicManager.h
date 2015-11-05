/******************************************************************************************************/
/* Manages a set of pdfs, recieves a list of parameters and passes them out to each of the systematics*/
/* and triggeres their reconstruction. Systematics inside are passed to a set of pdfs to change       */
/* them                                                                                               */
/******************************************************************************************************/

#ifndef __SYSTEMATIC_MANAGER__
#define __SYSTEMATIC_MANAGER__
#include <vector>
#include <Systematic.h>
#include <PdfMapping.h>

class SystematicManager{
 public:
    SystematicManager(): fNSystematics(0), fTotalParamCount(0) {}
    ~SystematicManager() {}

    void Add(Systematic*);
    const std::vector<Systematic*>& GetSystematics() const;
    
    void SetParameters(const std::vector<double>& params_);
    const std::vector<double>& GetParameters() const;

    size_t GetNSystematics() const;
    const PdfMapping& GetTotalResponse() const;
    
 private:
    std::vector<size_t>      fParamCounts;
    std::vector<Systematic*> fSystematics;
    std::vector<double>      fParams;

    PdfMapping fTotalResponse;

    size_t fTotalParamCount;
    size_t fNSystematics;
};
#endif
