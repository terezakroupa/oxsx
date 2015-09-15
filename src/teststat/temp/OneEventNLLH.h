/*****************************************************/
/* A class to calculate the nllh for a single event  */
/*****************************************************/

#ifndef __ONE_EV_NLLH__
#define __ONE_EV_NLLH__
#include <vector>
#include "../pdf/Pdf.h"
class OneEventNLLH{
 public:
    OneEventNLLH(const std::vector<Pdf*>& pdfs_);

    double Evaluate(const std::vector<double>& eventVals_) const;
    void   SetEventRates(const std::vector<double>& eventRates_);

 private:
    std::vector<Pdf*>   fPdfs;
    std::vector<double> fRates;

    size_t fNPdfs;
};
#endif
