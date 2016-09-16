#ifndef __OXSX_EVENT_CONVOLUTION__
#define __OXSX_EVENT_CONVOLUTION__
#include <EventSystematic.h>
#include <vector>
#include <string>
#include <iostream>
class IntegrableFunction;
class ConditionalDistribution;
class EventData;
class EventConvolution : public EventSystematic{
 public:
  // Constructors
  EventConvolution(): fDist(NULL){}
  ~EventConvolution();
  EventConvolution(const EventConvolution&);
  EventConvolution operator=(const EventConvolution&);

  // Get/Set
  void SetFunction(IntegrableFunction* f);
  void SetConditionalDistribution(ConditionalDistribution* f);

  // Event Systematic interface
  EventData operator()(const EventData&);
  
  // Fit Component interface defers to underlying function
  void MakeFittable();
  std::vector<std::string> GetParameterNames() const;
  std::vector<double> GetParameters() const;
  size_t GetParameterCount() const;
  void   SetParameters(const std::vector<double>&);

 private:
  ConditionalDistribution* fDist;
};
#endif
