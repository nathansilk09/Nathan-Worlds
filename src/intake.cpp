#include <cmath>
                 
#include "vex.h"
#include "intake.h"

void intakemove(){

if (Controller1.ButtonR1.pressing()) {
    intake.spin(fwd, -12, volt);
}

else if (Controller1.ButtonL1.pressing()) {
    intake.spin(fwd, 12, volt);
}

else {
    intake.stop();
    intake.setStopping(coast);
}

}

using namespace vex;  