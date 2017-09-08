#include <AxisCollection.h>
#include <Histogram.h>
#include <Combinations.hpp>

template<typename T1>
std::vector<Histogram> 
HistTools::MakeAllHists(const AxisCollection& axes_,
                        const T1& names_){
    std::vector<Histogram> hists;
    hists.reserve(names_.size());

    typedef typename T1::const_iterator It;
    for(It it = names_.begin(); it != names_.end(); ++it){
        AxisCollection axes;
        axes.AddAxis(axes_.GetAxis(*it));
        hists.push_back(Histogram(axes));
    }
    return hists;
}

template<typename T>
std::vector<T>
HistTools::GetVisualisableProjections(const T& hist_){
  typedef std::pair<std::string, std::string> AxisPair;
  typedef std::set<AxisPair> AxisCombs;

  std::vector<T> hists;
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
