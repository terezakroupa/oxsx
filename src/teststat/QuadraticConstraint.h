/***********************************************************************************************/
/* A quadratic constraint on a fit parameter, for log likelihood and Chi-Square tests this is  */
/* equivlent to a gaussian contraint.                                                          */
/***********************************************************************************************/
#ifndef __OXSX_QUADRATIC_CONSTRAINT__
#define __OXSX_QUADRATIC_CONSTRAINT__

class QuadraticConstraint{
 public:
 QuadraticConstraint(size_t paramIndex_, double mean_, double width_) : 
    fMean(mean_), fWidth(width_), fParamIndex(paramIndex_) {}

    double operator()(const std::vector<double>& vals_) const {
        double val = vals_.at(fParamIndex);
        return (val - fMean) * (val - fMean) / (fWidth * fWidth);
    }
    
 private:
    double fMean;
    double fWidth;
    size_t fParamIndex;
};
#endif
