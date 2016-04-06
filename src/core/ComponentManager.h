#ifndef __OXSX_COMPONENT_MANAGER__
#define __OXSX_COMPONENT_MANAGER__
#include <TunableComponent.h>
#include <vector>

class ComponentManager{
 public:
    ComponentManager() : fTotalParamCount(0), fComponentCount(0) {}
    void AddComponent(TunableComponent*);

    void SetParameters(const std::vector<double>&);
    std::vector<double> GetParameters() const;

 private:
    std::vector<TunableComponent*> fComponents;
    std::vector<int>               fParamCounts;

    int fTotalParamCount;
    int fComponentCount;
};
#endif
