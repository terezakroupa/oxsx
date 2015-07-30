#include <Pdf.h>
#include <CompositePdf.h>
#include <algorithm>

CompositePdf Pdf::operator* (const Pdf& other_) const {
    return CompositePdf(this, &other_);
}

unsigned Pdf::GetNDims() const{
    return fNDims;
}
