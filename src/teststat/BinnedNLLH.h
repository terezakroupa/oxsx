#ifndef __BinnedNLLH__
#define __BinnedNLLH__
#include <TestStatistic.h>
#include <BinnedPhysDistMan.h>
#include <SystematicManager.h>
#include <BinnedPhysDistShrink.h>
#include <ComponentManager.h>
#include <DataSet.h>
#include <CutCollection.h>
#include <QuadraticConstraint.h>
#include <map>
#include <vector>

class DataSet;
class BinnedNLLH : public TestStatistic{
 public:
    BinnedNLLH() : fCalculatedDataPdf(false), fAlreadyShrunk(false), fDataSet(NULL) {}

    void   SetPdfManager(const BinnedPhysDistMan&);
    void   SetSystematicManager(const SystematicManager&);

    void   AddPdf(const BinnedPhysDist&);
    void   AddSystematic(Systematic*);

    void   AddPdfs(const std::vector<BinnedPhysDist>&);
    void   AddSystematics(const std::vector<Systematic*>);

    void   SetConstraint(const std::string& paramName_, double mean_, double sigma_);
    
    void SetNormalisations(const std::vector<double>& norms_);
    std::vector<double> GetNormalisations() const;

    void  BinData();

    void SetDataPdf(const BinnedPhysDist&);
    BinnedPhysDist GetDataPdf() const;

    void SetDataSet(DataSet*);
    DataSet* GetDataSet();

    void SetBuffer(size_t dim_, unsigned lower_, unsigned upper_);
    std::pair<unsigned, unsigned> GetBuffer(size_t dim_) const;
    void SetBufferAsOverflow(bool b_); // true by default
    bool GetBufferAsOverflow() const;

    void AddCut(const Cut&);
    void SetCuts(const CutCollection&);

    // Test statistic interface
    void RegisterFitComponents(); 
    void SetParameters(const std::vector<double>&);
    std::vector<double> GetParameters() const;
    int  GetParameterCount() const;
    double Evaluate();
    std::vector<std::string> GetParameterNames() const;

 private:
    BinnedPhysDistMan  fPdfManager;
    SystematicManager fSystematicManager;
    BinnedPhysDistShrink fPdfShrinker;
    DataSet* fDataSet;
    CutCollection fCuts;
    std::map<std::string, QuadraticConstraint> fConstraints;

    BinnedPhysDist fDataPdf;
    bool      fCalculatedDataPdf;
    bool      fAlreadyShrunk;
    ComponentManager fComponentManager;    
};
#endif
