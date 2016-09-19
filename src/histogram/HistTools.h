#ifndef __OXSX_HIST_TOOLS__
#define __OXSX_HIST_TOOLS__
#include <vector>
class AxisCollection;
class Histogram;

class HistTools{
 public:
    static std::vector<Histogram> MakeAllHists(const AxisCollection&, 
                                               const std::vector<std::vector<size_t> > combinations_);
};
#endif

