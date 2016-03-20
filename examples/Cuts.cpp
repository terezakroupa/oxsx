/*
Cuts are functions that take an event and return true or false, depending on whether the event passes the cut or not.

Cuts can be grouped together into a cut collection, which returns true if all cuts are satisfied.
The CutCollection object is used to FillPdfs or generate data sets, only taking events that pass 
*/
#include <BoxCut.h>
#include <BoolCut.h>
#include <EventData.h>

int main(){
    // cut if first observable is bigger than zero
    BoxCut
}
