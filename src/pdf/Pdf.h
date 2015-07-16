/***********************************************/
/* An abstract base class to represent a pdf.  */
/***********************************************/

#ifndef __PDF__
#define __PDF__
#include <vector>

class Pdf{
 public:
    virtual double operator() (const std::vector<double>* vals_) const = 0;  
    virtual double operator() (const std::vector<double>* vals_, 
                               const std::vector<size_t>& indicies_) const = 0;  
    virtual ~Pdf() {}
};

#endif
