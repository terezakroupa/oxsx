#include "Pdf.h"
#include "CompositePdf.h"

CompositePdf Pdf::operator* (const Pdf& other_) const {
    return CompositePdf(this, &other_);
}
