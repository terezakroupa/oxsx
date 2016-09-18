/***************************************************************************************************/
/* The outer product of two pdfs is also a pdf composite = pdf1 * pdf2                             */
/* This implemented here using recursion, so any level of composition can be used.                 */
/* This class owns its own copies of constituent pdfs                                              */
/* Calls to operator() and Probability() are forwarded to the constituent pdfs, in the latter case */
/* each will know where to look from its data representation                                       */
/***************************************************************************************************/

#ifndef __COMPOSITE_PHYSDIST__
#define __COMPOSITE_PHYSDIST__
#include <PhysDist.h>
#include <vector>
class EventData;

class CompositePhysDist : public PhysDist{
 public:
    CompositePhysDist(const PhysDist* p1_, const PhysDist* p2_);
    CompositePhysDist(const std::vector<PhysDist*>& pdfs_); 
    virtual ~CompositePhysDist();

    virtual double operator() (const std::vector<double>& vals_) const;
    virtual double Probability(const EventData&) const;
    virtual PhysDist*   Clone() const; // required for futher compositions

    virtual double Integral()  const;
    virtual void   Normalise();
    unsigned GetNDims() const;
 private:
    
    std::vector<PhysDist*> fDistPtrs;
};

CompositePhysDist operator * (const PhysDist&, const PhysDist&);

#endif
