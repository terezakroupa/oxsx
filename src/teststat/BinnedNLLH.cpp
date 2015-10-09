#include <BinnedNLLH.h>
#include <math.h>
#include <DataSet.h>
#include <iostream>
#include <PdfExceptions.h>
#include <DataExceptions.h>

double 
BinnedNLLH::Evaluate(){
    if(!fDataSet) 
        throw DataException("BinnedNNLH function called with no data set! set this first");
    

    if (!fCalculatedDataPdf){
        BinData();
    }

    // Adjust Systematics if they have changed
    fSystematicManager.SetParameters(fSystematicParams);

    // Apply systematics
    fPdfManager.ApplySystematics(fSystematicManager);

    // Set Normalisations
    fPdfManager.SetNormalisations(fNormalisations);

    // loop over bins and calculate the likelihood
    double nLogLH = 0;
    for(size_t i = 0; i < fDataPdf.GetNBins(); i++){
        double prob = fPdfManager.BinProbability(i);
        if(prob){
            nLogLH -= fDataPdf.GetBinContent(i) *  log(prob);
        }
    }

    // Extended LH correction
    for(size_t i = 0; i < fNormalisations.size(); i++)
        nLogLH += fNormalisations.at(i);
            
    // Constraints
    for(size_t i = 0; i < fSystematicConstraints.size(); i++)
        nLogLH += fSystematicConstraints.at(i).operator()(fSystematicParams);
    
    for(size_t i = 0; i < fNormalisationConstraints.size(); i++)
        nLogLH += fNormalisationConstraints.at(i).operator()(fNormalisations);

    return nLogLH;
}

void
BinnedNLLH::BinData(){
    BinnedPdf dataPdf(fPdfManager.GetOriginalPdf(0)); // make a copy for same binning and data rep
    dataPdf.Empty();
    for(size_t i = 0; i < fDataSet -> GetNEntries(); i++){
        EventData dat = fDataSet -> GetEntry(i);
        dataPdf.Fill(dat);
    }

    fDataPdf = dataPdf;
    fCalculatedDataPdf = true;
}

void
BinnedNLLH::SetPdfManager(const BinnedPdfManager& man_){
    fPdfManager = man_;
    fNpdfs = man_.GetNPdfs();
}

void
BinnedNLLH::SetSystematicManager(const SystematicManager& man_){
    fSystematicManager = man_;
    fNsystematics = man_.GetNSystematics();
}

void
BinnedNLLH::AddSystematicConstraint(const QuadraticConstraint& constr_){
    fSystematicConstraints.push_back(constr_);
}

void
BinnedNLLH::SetSystematicConstraint(size_t index_, const QuadraticConstraint& constr_){
    if(index_ >= fSystematicConstraints.size())
        throw DimensionError("Tried to set systematic constraint that doesn't exist : logic error");
    fSystematicConstraints[index_] = constr_;
}


void
BinnedNLLH::AddNormalisationConstraint(const QuadraticConstraint& constr_){
    fNormalisationConstraints.push_back(constr_);
}

void
BinnedNLLH::SetNormalisationConstraint(size_t index_, const QuadraticConstraint& constr_){
    if(index_ >= fNormalisationConstraints.size())
        throw DimensionError("BinnedNNLH::Tried to set systematic constraint that doesn't exist : logic error");
    fNormalisationConstraints[index_] = constr_;
}

QuadraticConstraint
BinnedNLLH::GetNormalisationConstraint(size_t index_) const{
    if(index_ >= fNormalisationConstraints.size())
        throw DimensionError("BinnedNLLH::Attempted access on non existent constraint");
    return fNormalisationConstraints.at(index_);
}


QuadraticConstraint
BinnedNLLH::GetSystematicConstraint(size_t index_) const{
    if(index_ >= fSystematicConstraints.size())
        throw DimensionError("BinnedNLLH::Attempted access on non existent constraint");
    return fSystematicConstraints.at(index_);
}

void
BinnedNLLH::AddPdf(const BinnedPdf& pdf_){
    fPdfManager.AddPdf(pdf_);
    fNpdfs++;
}

void 
BinnedNLLH::AddSystematic(Systematic sys_){
    fSystematicManager.Add(&sys_);
    fNsystematics++;
}
