#include <Gaussian.h>
#include <Convolution.h>
#include <BinnedPdf.h>
#include <PdfConverter.h>

int main(){
    
    // Test it on a binned pdf
    Gaussian testGaus(std::vector<double>(2,1), std::vector<double>(2,2)); // means then sigmas
    AxisCollection axes;
    axes.AddAxis(PdfAxis("energy", 2, 3, 10, "Energy"));
    axes.AddAxis(PdfAxis("radius", 2, 3, 10, "rad"));

    BinnedPdf testPdf = PdfConverter::ToBinnedPdf(testGaus, axes);

    Gaussian gausPdf(1, 2); // mean sigma
    Convolution conv;

    conv.SetPdf(&gausPdf);
    conv.SetAxes(axes);

    // What indicies matter?
    std::vector<size_t> smearDimensions(1, 0); // just first index for smear
    DataRepresentation  smearRep(smearDimensions);

    // pdfs to act on will be in E and r
    smearDimensions.push_back(1);
    DataRepresentation pdfRep(smearDimensions);

    conv.SetDataRep(smearRep);
    conv.SetPdfDataRep(pdfRep);
    
    // Build the internal matrix
    conv.Construct();

    // Now use it 
    BinnedPdf transformed = conv(testPdf);
                             
    return 0;
}
