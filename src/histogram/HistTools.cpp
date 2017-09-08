#include <HistTools.h>
#include <Histogram.h>
#include <ContainerTools.hpp>
#include <Combinations.hpp>

std::vector<Histogram>
HistTools::MakeAllHists(const AxisCollection& axes_,
                        const std::set<std::pair<std::string, std::string> >& combinations_){
    std::vector<Histogram> hists;
    hists.reserve(combinations_.size());
    
    typedef std::set<std::pair<std::string, std::string> >::iterator SetIt;

    for(SetIt it = combinations_.begin(); it != combinations_.end(); ++it){
        AxisCollection axes;
        axes.AddAxis(axes_.GetAxis(it->first));
        axes.AddAxis(axes_.GetAxis(it->second));
            
        hists.push_back(Histogram(axes));
    }
    return hists;
}

void
HistTools::FillAllHists(std::vector<Histogram>& hists_, const std::map<std::string, double>& fillVals_){
    // note this assumes that the histograms have axes that match the keys of fillvals throws otherwise
    for(size_t i = 0; i < hists_.size(); i++){
        hists_.at(i).Fill(fillVals_);
    }    
}

std::vector<Histogram>
HistTools::GetVisualisableProjections(const Histogram& hist_){
  typedef std::pair<std::string, std::string> AxisPair;
  typedef std::set<AxisPair> AxisCombs;

  std::vector<Histogram> hists;
  size_t dim  = hist_.GetNDims();
  hists.reserve(dim + dim * (dim -1)/2);
  
  std::vector<std::string> axisNames = hist_.GetAxes().GetAxisNames();
  // 1D
  for(size_t i = 0; i < axisNames.size(); i++){
    hists.push_back(hist_.Marginalise(axisNames.at(i)));
  }
  
  // 2D
  AxisCombs combs = Combinations::AllCombsNoDiag(axisNames);
  for(AxisCombs::iterator it = combs.begin(); it != combs.end(); ++it){
    // sadly this method takes a vector not a pair so conv
    std::vector<std::string> vec;
    vec.push_back(it->first);
    vec.push_back(it->second);
    hists.push_back(hist_.Marginalise(vec));
  }
  return hists;
}
