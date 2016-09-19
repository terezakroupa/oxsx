#ifndef __OXSX_EVENT_CONVOLUTION__
#define __OXSX_EVENT_CONVOLUTION__
#include <EventSystematic.h>
#include <vector>
#include <string>
#include <iostream>

class PDF;
class ConditionalPDF;
class Event;
class EventConvolution : public EventSystematic{
 public:
  // Constructors
  EventConvolution(): fDist(NULL){}
  ~EventConvolution();
  EventConvolution(const EventConvolution&);
  EventConvolution operator=(const EventConvolution&);

  // Get/Set
  void SetPDF(PDF* f);
  void SetConditionalPDF(ConditionalPDF* f);

  // Event Systematic interface
  Event operator()(const Event&);
  
  // Fit Component interface defers to underlying function
  void MakeFittable();
  std::vector<std::string> GetParameterNames() const;
  std::vector<double> GetParameters() const;
  size_t GetParameterCount() const;
  void   SetParameters(const std::vector<double>&);

 private:
  ConditionalPDF* fDist;
};
#endif
