#ifndef __OXSX_CONTAINER_PARAMETER__
#define __OXSX_CONTAINER_PARAMETER__
#include <FitParameter.h>
#include <stddef.h>
#include <iterator>
#include <vector>
#include <string>

// Class definition
template<typename Container>
class ContainerParameter : public FitParameter{
public:
    typedef typename std::iterator_traits<typename Container::iterator>::iterator_category Category;

 ContainerParameter(const std::string& nm_, Container& cntr_, size_t index_) : fName(nm_), fContainer(cntr_), fIndex(index_) {}
    void   Set(double);
    double Get() const;

    std::string GetName() const {return fName;}
    void SetName(const std::string& nm_){fName = nm_;}

private:
    Container& fContainer;
    size_t     fIndex;
    std::string fName;
};

// Implementations of the finding algorithm, optimised by iterator type
template<typename Container>
double&
GetNth(Container& C_, size_t n_, std::random_access_iterator_tag);

template<typename Container>
double&
GetNth(Container& C_, size_t n_, std::bidirectional_iterator_tag);

template<typename Container>
double&
GetNth(Container& C_, size_t n_, std::forward_iterator_tag);

// Typedef main usecase - std vec
typedef ContainerParameter<std::vector<double> > VectorParameter;

// Implementation in the header below
#include "ContainerParameter.hpp"
#endif
