template<typename LogLikelihood>
double
HMCEnergy<LogLikelihood>::Evaluate(){
    return -fLLikelihood.Evaluate();
}


template<typename LogLikelihood>
void
HMCEnergy<LogLikelihood>::SetParameters(const ParameterDict& p_){
    fLLikelihood.SetParameters(p_);
}

