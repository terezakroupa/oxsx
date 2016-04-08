#ifndef __BinnedNLLH__
#define __BinnedNLLH__
#include <TestStatistic.h>
#include <BinnedPdfManager.h>
#include <SystematicManager.h>
#include <BinnedPdfShrinker.h>
#include <vector>
#include <QuadraticConstraint.h>

class BinnedNLLH : public TestStatistic{
 public:
    BinnedNLLH() : fCalculatedDataPdf(false) {}
    ~BinnedNLLH(){}

    double Evaluate();

    void   SetPdfManager(const BinnedPdfManager&);
    void   SetSystematicManager(const SystematicManager&);

    void   AddPdf(const BinnedPdf&);
    void   AddSystematic(Systematic*);

    void   AddPdfs(const std::vector<BinnedPdf>&);
    void   AddSystematics(const std::vector<Systematic*>);

    void AddSystematicConstraint(const QuadraticConstraint& constr_);
    void AddNormalisationConstraint(const QuadraticConstraint& constr_);

    void SetSystematicConstraint(size_t index_, const QuadraticConstraint& constr_);
    void SetNormalisationConstraint(size_t index_, const QuadraticConstraint& constr_);

    QuadraticConstraint GetSystematicConstraint(size_t index_)    const;
    QuadraticConstraint GetNormalisationConstraint(size_t index_)  const;

    void SetNormalisations(const std::vector<double>& norms_);
    std::vector<double> GetNormalisations() const;

    void  BinData();
    virtual void SetDataSet(DataSet*);

    void SetDataPdf(const BinnedPdf&);
    BinnedPdf GetDataPdf() const;

    void SetBuffer(size_t dim_, unsigned lower_, unsigned upper_);
    std::pair<unsigned, unsigned> GetBuffer(size_t dim_) const;
    void SetBufferAsOverflow(bool b_); // true by default
    bool GetBufferAsOverflow() const;
    
    // Set up for the fit
    void RegisterFitComponents(); // decalare which objects should be adjusted by the fit
    
 private:
    BinnedPdfManager  fPdfManager;
    SystematicManager fSystematicManager;
    BinnedPdfShrinker fPdfShrinker;

    std::vector<QuadraticConstraint> fSystematicConstraints;
    std::vector<QuadraticConstraint> fNormalisationConstraints;
    
    BinnedPdf fDataPdf;
    bool      fCalculatedDataPdf;
    
    
};
#endif
