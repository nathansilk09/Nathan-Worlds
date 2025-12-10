#include <cmath>
                 
#include "vex.h"
#include "intake.h"

int intake_toggle = 0;

void intakemove(){

if (Controller1.ButtonL1.pressing()){
    if (intake_toggle != 1){
        intake_toggle = 1;
    }
    else {
        intake_toggle = 0;
    }
}

if (Controller1.ButtonR1.pressing()){
    if (intake_toggle != 2){
        intake_toggle = 2;
    }
    else {
        intake_toggle = 0;
    }
}

if (Controller1.ButtonUp.pressing()){
    intake_toggle = 0;
}

if (intake_toggle == 1) {
    intake.spin(fwd, -12, volt);
}

else if (intake_toggle == 2) {
    intake.spin(fwd, 12, volt);
}

else {
    intake.stop();
    intake.setStopping(coast);
}

}

using namespace vex;  