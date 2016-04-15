/*****************************************************************************************************/
/* Abstract base class for a pdf. In this context a pdf is anything that takes a set of observations */
/* and returns a probability.                                                                        */
/* Each pdf owns a DataRepresentation, that contains the list of indicies it should act on.          */
/*                                                                                                   */
/* For example, if the data comes as triplets (x, y, z), but the pdf is only concerned with the first*/
/* and last observables (perhaps the others are ignored or dealt with by another pdf) the rep will   */
/* contian the indicies (0, 2)                                                                       */
/* The method Probability() then simply picks these indicies out of the EventData and passes them to */
/* the operator(). This is implemented at the Pdf level and does not need to be repeated in inherited*/
/* classes                                                                                           */
/*                                                                                                   */
/* Composition of Pdfs is achieved using recursion. For inheriting classes to use this feature they  */
/* must implement Clone() and ideally the copy constructor. Clone should return a Pdf* to a deep     */
/* copy of the obect. Then the following will work                                                   */
/*                                                                                                   */
/* CompositePdf comp = pdf1 * pdf2; where pdf1 and pdf2 are any classes Derived from this one        */
/*****************************************************************************************************/

#ifndef __PDF__
#define __PDF__
#include <vector>
#include <string>
#include <DataRepresentation.h>
#include <EventData.h>

class Pdf{
 public:
    virtual ~Pdf() {}

    virtual double operator()  (const std::vector<double>& vals_) const = 0;
    virtual double Probability (const EventData&) const = 0;
    
    virtual double Integral() const = 0;

    virtual void   Normalise()   = 0;
    virtual Pdf*   Clone() const = 0;

    virtual unsigned GetNDims() const = 0;    
};
#endif
