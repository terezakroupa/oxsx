#ifndef __OXSX_CUT_COLLECTION__
#define __OXSX_CUT_COLLECTION__
#include <vector>
#include <string>
class EventData;
class Cut;
class CutLog;

class CutCollection{
 public:
  CutCollection() {}
  CutCollection(const CutCollection&);
  CutCollection& operator=(const CutCollection&); // deep copy
  ~CutCollection(); // frees cuts

  bool PassesCuts(const EventData& event_) const;
  bool PassesCuts(const EventData& event_, CutLog& log_) const;

  void AddCut(const Cut&);
  void AddCut(const Cut&, const std::string&);

  std::vector<std::string> GetCutNames() const;
  
 private:
  std::vector<Cut*> fCuts;
  std::vector<std::string> fCutNames;
};
#endif
