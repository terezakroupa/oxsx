#ifndef __OXSX_KDEPDF__
#define __OXSX_KDEPDF__
#include <Function.h>
#include <DenseMatrix.h>
#include <Vector.h>
#include <Pdf.h>

class KDEPdf : public Pdf{
 public:
    // Constructory things, dynamic copy kernel_
    KDEPdf(Function* kernel_, const DenseMatrix& bwMat_, double bwScale_); 
    KDEPdf(Function* kernel_, double bwScale_);     // assumes identity bw
    KDEPdf(const KDEPdf&); // deep copy fkernel

    virtual Pdf* Clone() const;

    ~KDEPdf(); // frees fKernel

    // Getters/Setters
    void   SetBandwidthScale(double);
    double GetBandwidthScale() const;

    void      SetKernel(Function*);
    Function* GetKernel() const;

    void SetBandwidthMatrix(const DenseMatrix&);
    DenseMatrix GetBandwidthMatrix() const;
    
    // Pdf overrides
    virtual double operator()(const std::vector<double>& vals_) const;
    virtual double Integral() const {return 1;}
    virtual void   Normalise() {}    

    // Fill methods
    void Fill(const std::vector<double>& vals_);
    void Fill(const EventData& data_);
    void Fill(double val_);
    void Clear();
    void Reserve(int n);
    int  GetEntries() const;
    
    double GetPrefactor() const;

 private:
    void        Initialise(Function*, const DenseMatrix&, double);

    Function*   fKernel;
    DenseMatrix fBandwidthMat;
    DenseMatrix fBandwidthMatInverse;
    double      fBandwidthScale;
    std::vector<Vector> fPoints;
};
#endif
