#ifndef __OXSX_INTEGRABLE_FUNCTION__
#define __OXSX_INTEGRABLE_FUNCTION__
#include <Function.h>
// Remember to implement MakeFittable!!

class IntegrableFunction : public Function{
 public:
    virtual ~IntegrableFunction() {}

    virtual double Integral(const std::vector<double>& mins_,
                            const std::vector<double>& maxs_) const = 0;

    virtual double Integral() const = 0;
	virtual std::vector<double> Sample() const = 0;
};
#endif
