#include <HistTools.h>
#include <Histogram.h>

std::vector<Histogram>
HistTools::MakeAllHists(const std::vector<PdfAxis>& axes_,
                        const std::vector<std::vector<size_t> > combinations_){
    std::vector<Histogram> hists;
    hists.reserve(combinations_.size());
    for(size_t i = 0; i < combinations_.size(); i++){
        const std::vector<size_t>& dims = combinations_.at(i);
        AxisCollection axes;
        for(size_t j = 0; j < dims.size(); j++){
            axes.AddAxis(axes_.at(dims.at(j)));
        }
        hists.push_back(Histogram(axes));
    }
    return hists;
}
