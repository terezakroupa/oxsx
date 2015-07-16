/*********************************************************/
/* A class that represents an event type in the detector */
/*********************************************************/
#ifndef __EVENT__
#define __EVENT__
#include <vector>
#include <string>
class Pdf;

class Event{
 public:
    Event(const std::vector<const Pdf*>& pdfs_, const std::vector<std::vector<size_t> >& indicies_,
          const std::string& name_, const std::string& latexName_ = "");

    Event(const Pdf* pdf_,
          const std::string& name_, const std::string& latexName_ = "");
    ~Event() {}

    double Probability(const std::vector<double>* vals_) const;
    std::string GetName() const {return fName;}
    std::string GetLatexName() const {return fLatexName;}
    void SetName(const std::string& name_);
    void SetLatexName(const std::string& latexName_);

 private:
    std::vector<const Pdf*> fPDFs;
    std::vector<std::vector<size_t> > fIndicies;
    std::string fName;
    std::string fLatexName;

    bool fOnePdf;
    double OnePdfProbability(const std::vector<double>* vals_) const;
    double MultiPdfProbability(const std::vector<double>* vals_) const;
};
#endif
