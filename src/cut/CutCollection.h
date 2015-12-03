#ifndef __OXSX_CUT_COLLECTION__
#define __OXSX_CUT_COLLECTION__
#include <vector>
class EventData;
class Cut;

class CutCollection{
 public:
  CutCollection(){}
  CutCollection(const CutCollection&);
  CutCollection& operator=(const CutCollection&); // deep copy
  ~CutCollection(); // frees cuts

  bool PassesCuts(const EventData& event_) const;

  void AddCut(const Cut&);
  
 private:
  std::vector<Cut*> fCuts;
  
};
#endif
