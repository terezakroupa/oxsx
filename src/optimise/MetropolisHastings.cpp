#include <MetropolisHastings.h>
#include <Rand.h>
#include <math.h> //sqrt
#include <iostream>

const std::vector<double>&
MetropolisHastings::GetSigmas() const{
    return fSigmas;
}

void
MetropolisHastings::SetSigmas(const std::vector<double>& sigmas_){
    fSigmas = sigmas_;
}

unsigned
MetropolisHastings::GetBurnIn() const{
    return fBurnIn;
}

void
MetropolisHastings::SetBurnIn(unsigned burnIn_){
    fBurnIn = burnIn_;
}

unsigned
MetropolisHastings::GetThinFactor() const{
    return fThinFactor;
}

void
MetropolisHastings::SetThinFactor(unsigned thinFac_){
    fThinFactor = thinFac_;
}

unsigned
MetropolisHastings::GetMaxIter() const{
    return fMaxIter;
}

void
MetropolisHastings::SetMaxIter(unsigned maxIter_){
    fMaxIter = maxIter_;
}

double
MetropolisHastings::GetRejectionRate() const{
    return fRejectionRate;
}

std::vector<double>
MetropolisHastings::GetMinima() const{
    return fMinima;
}

void
MetropolisHastings::SetMinima(const std::vector<double>& minima_){
    fMinima = minima_;
}


std::vector<double>
MetropolisHastings::GetMaxima() const{
    return fMaxima;
}

void
MetropolisHastings::SetMaxima(const std::vector<double>& maxima_){
    fMaxima = maxima_;
}


void
MetropolisHastings::SetFlipSign(bool b_){
    fFlipSign = b_;
}

bool
MetropolisHastings::GetFlipSign() const{
    return fFlipSign;
}

FitResult
MetropolisHastings::Optimise(){
    fNDims = fMinima.size();
    fRejectionRate = 0;
    fBestFit.resize(fNDims, 0);
    fMaxVal = 0;

    // 1. Choose a random starting point
    std::vector<double> currentStep;
    for(size_t i = 0; i < fMinima.size(); i++){
        currentStep.push_back(fMinima.at(i) + Rand::Uniform() * (fMaxima.at(i) - fMinima.at(i)));
    }
    fSample.empty();
    fSample.reserve(fMaxIter - fBurnIn);
    // 2. Loop step through the space a fixed number of times and
    for(unsigned i = 0; i < fMaxIter; i++){
        // a. Save the point in question if you are past burn-in phase and according to thinning
      if (i > fBurnIn && !(i%fThinFactor))
            fSample.push_back(currentStep);
      
        if(!(i%1000))
            std::cout << i << "  /  " << fMaxIter << std::endl;


        // b. Propose a new step according to a random jump distribution
        std::vector<double> proposedStep = JumpDraw(currentStep);

        // c. Test for acceptance
        if (StepAccepted(currentStep, proposedStep))
            currentStep = proposedStep;
        else
            fRejectionRate++;
        
    }
    fRejectionRate/= static_cast<double>(fMaxIter);
    std::cout << "Metropolis Hastings:: rejection rate = " << fRejectionRate << std::endl;

    fFitResult.SetBestFit(fBestFit);
    fFitResult.SetStatSample(fSample);
    return fFitResult;
}

bool
MetropolisHastings::StepAccepted(const std::vector<double>& thisStep_, 
                                 const std::vector<double>& proposedStep_){

    // dont step outside of the fit region 
    for (size_t i = 0; i < fMinima.size(); i++){
        if (proposedStep_.at(i) < fMinima.at(i) || proposedStep_.at(i) > fMaxima.at(i))
            return false;
    }

    pTestStatistic -> SetParams(thisStep_);
    double thisVal = pTestStatistic -> Evaluate();
    
    pTestStatistic -> SetParams(proposedStep_);
    double proposedVal = pTestStatistic -> Evaluate();

    if(fFlipSign){
        thisVal = -thisVal;
	proposedVal = -proposedVal;
    }

    if(thisVal > fMaxVal){
        fMaxVal = thisVal;
        fBestFit = thisStep_;
    }

    double acceptanceParam = JumpProbRatio(thisStep_, proposedStep_) * proposedVal/thisVal;

    if (acceptanceParam > 1)
        return true;

    else if (acceptanceParam >= Rand::Uniform())
        return true;

    else{
        return false;
    }
}

std::vector<double> 
MetropolisHastings::JumpDraw(const std::vector<double>& thisStep_) const{
    std::vector<double> newStep(thisStep_);
    for(size_t i = 0; i < newStep.size(); i++){
        newStep[i] = thisStep_.at(i) + Rand::Gaus(0, fSigmas.at(i));
    }
    return newStep;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
// std::vector<double>                                                                             //
// MetropolisHastings::JumpDraw(const std::vector<double>& thisStep_) const{                       //
//     double stepSize = Rand::Gaus(0, fSigma);                                                    //
//                                                                                                 //
//     // choose random direction on NParam -1 Sphere according to                                 //
//     // http://mathworld.wolfram.com/HyperspherePointPicking.html (Muller 1959, Marsaglia 1972)  //
//                                                                                                 //
//     std::vector<double> newPoint;                                                               //
//     double norm = 0;                                                                            //
//     for(size_t i = 0; i < fNDims; i++){                                                         //
//         double component = Rand::Gaus();                                                        //
//         newPoint.push_back(component);                                                          //
//         norm += component * component;                                                          //
//     }                                                                                           //
//                                                                                                 //
//     norm = sqrt(norm);                                                                          //
//     for(size_t i = 0; i < fNDims; i++){                                                         //
//         newPoint[i] *= stepSize/norm;                                                           //
//     }                                                                                           //
//                                                                                                 //
//     // Add to orginal vector and return                                                         //
//     for(size_t i = 0; i < fNDims; i++)                                                          //
//         newPoint[i] += thisStep_.at(i);                                                         //
//                                                                                                 //
//     return newPoint;                                                                            //
// }                                                                                               //
/////////////////////////////////////////////////////////////////////////////////////////////////////
