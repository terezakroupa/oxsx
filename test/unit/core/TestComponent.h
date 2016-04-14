#ifndef __OXSX_TEST_COMPONENT__
#define __OXSX_TEST_COMPONENT__
#include <FitComponent.h>
#include <ContainerParameter.h>
#include <DoubleParameter.h>
#include <sstream>
#include <list>
#include <vector>

class TestComponent : public FitComponent{
 public:
 TestComponent() : fDoubleParameter(0) {}
    std::vector<double> fVectorParameters;
    double fDoubleParameter;
    std::list<double> fListParameters;

    void ExposedSetParameterNames(const std::vector<std::string>& names_) {
        SetParameterNames(names_);
    }

    void MakeFittable() {
        EmptyParameters();
        fVectorParameters.resize(10, 0);
        fListParameters.resize(10, 0);

        AddAsParameter(new DoubleParameter(fDoubleParameter), "double");
        AddContainerOfParameters<std::list<double> >(fListParameters, "list");
        for(size_t i = 0; i < fVectorParameters.size(); i++){
            std::stringstream ss;
            ss << "vector " << i;
            AddAsParameter(new ContainerParameter<std::vector<double> >(fVectorParameters, i), ss.str());
        }
    }

};

#endif
