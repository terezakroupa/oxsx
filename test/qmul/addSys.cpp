#include <Gaussian.h>
#include <Convolution.h>
#include <BinnedPdf.h>
#include <PdfConverter.h>

int main(){
    
    Gaussian    gausPdf(1, 2); // mean sigma
    Convolution conv;


    // 1. What are you convolving with, what is the binning?
    conv.SetPdf(&gausPdf);
    conv.SetAxes(axes);

    // 2. What indicies does it act on, what indicies are the pdfs binned in?


    // pdfs to act on will be in dimensions 0 & 1, say energy & radius
    std::vector<size_t> pdfIndicies;
    pdfIndicies.push_back(0);
    pdfIndicies.push_back(1);
    DataRepresentation  pdfRep(pdfIndicies);
    DataRepresentation  smearRep(0);          //only smear in dimension 0, energy 

    conv.SetDataRep(smearRep);
    conv.SetPdfDataRep(pdfRep);

    // add this to the likelihood function, mean and sigma of gaussian are automatically
    // added to the list of parameters in LH
    lhFunction.AddSystematic(conv);
                             
    return 0;
}
