#include <cmath>
                 
#include "vex.h"
#include "Pnuematic.h"

bool BPA = true;

void pnuematicsgo(){

if (Controller1.ButtonUp.pressing() && !BPA) {
    BPA = true;
    wait(.2, seconds);
}
else if (Controller1.ButtonUp.pressing()){
    BPA = false;
    wait(.2, seconds);
}

if (BPA) {
    PA.set(false);
}
else {
    PA.set(true);
}   

}

using namespace vex;  