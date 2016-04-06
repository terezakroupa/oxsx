#include <KDEPdf.h>
#include <PdfExceptions.h>
#include <math.h>

// Constructory things
void
KDEPdf::Initialise(Function* kernel_, 
                   const DenseMatrix& mat_, double scale_){
    // now allocate the memory
    fNDims  = kernel_->GetNDims();
    fKernel = kernel_->Clone();
    fBandwidthScale = scale_;
    SetBandwidthMatrix(mat_);
    
}

KDEPdf::KDEPdf(Function* kernel_, const DenseMatrix& bwMat_, double scale_){
    Initialise(kernel_, bwMat_, scale_);
}

KDEPdf::KDEPdf(Function* kernel_, double scale_){
    DenseMatrix m;
    m.Identity(kernel_->GetNDims());
    Initialise(kernel_, m, scale_);
    
}

KDEPdf::~KDEPdf(){
    delete fKernel;
}

KDEPdf::KDEPdf(const KDEPdf& other_){
    fNDims  = other_.fNDims;
    SetBandwidthMatrix(other_.fBandwidthMat);
    fKernel = other_.fKernel->Clone();
}

Pdf*
KDEPdf::Clone() const{
    return new KDEPdf(*this);
}

// Fill methods
void
KDEPdf::Fill(const std::vector<double>& vals_){
    if(vals_.size() != fNDims)
        throw DimensionError("Tried to fill KDEPdf with wrong number of vals!");
    fPoints.push_back(vals_);
}

void
KDEPdf::Fill(const EventData& data_){
    Fill(data_.ToRepresentation(fDataRep));
}

void 
KDEPdf::Fill(double val_){
    if(fNDims != 1)
        throw 0;
    fPoints.push_back(std::vector<double>(1, val_));
}

void 
KDEPdf::Clear(){
    fPoints.clear();
}

void
KDEPdf::Reserve(int n){
    fPoints.reserve(n);
}

int 
KDEPdf::GetEntries() const{
    return fPoints.size();
}

// Getters/Setters
Function*
KDEPdf::GetKernel() const{
    return fKernel->Clone();
}

void
KDEPdf::SetKernel(Function* kern_){
    // FIXME::LEAK!
    //    delete fKernel;
    fKernel = kern_->Clone();
}

void
KDEPdf::SetBandwidthMatrix(const DenseMatrix& mat_){
    if (mat_.GetNCols() != mat_.GetNRows())
        throw DimensionError("KDE bandwidth matrix must be square!");

    if (mat_.GetNCols() != fKernel->GetNDims())
        throw DimensionError("KDE Bandwidth matrix must have same dimensionality as kernel");
    
    try{
        fBandwidthMatInverse = mat_.Inverse();
    }
    catch(const std::runtime_error& e){
        throw std::runtime_error("KDE Bandwidth matrix must be invertible!");
    }
    fBandwidthMat = mat_;
}

DenseMatrix
KDEPdf::GetBandwidthMatrix() const{
    return fBandwidthMat;
}

void
KDEPdf::SetBandwidthScale(double val_){
    fBandwidthScale = val_;
}

double
KDEPdf::GetBandwidthScale() const{
    return fBandwidthScale;
}


// This is the main method
double 
KDEPdf::operator()(const std::vector<double>& vals_) const{
    double sum = 0;
    Vector p;
    Vector testVal(vals_);

    for(size_t i = 0; i < fPoints.size(); i++){
        p = (fPoints.at(i) - testVal).Scalar(1/fBandwidthScale);
        sum += fKernel -> Call1D(sqrt(p.Inner(fBandwidthMatInverse.Inner(p))));
    }
    return sum/GetPrefactor();
}

double
KDEPdf::GetPrefactor() const{
    return GetEntries() * pow(fBandwidthScale, fNDims);
}
