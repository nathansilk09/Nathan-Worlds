#include <cmath>
                 
#include "vex.h"
#include "intake_outake.h"

int intake_toggle = 0;

void intakemove(){

if (Controller1.ButtonL1.pressing()){
    if (intake_toggle != 1){
        intake_toggle = 1;
    }
    else {
        intake_toggle = 0;
    }
    wait(.3, seconds);
}

if (Controller1.ButtonR1.pressing()){
    if (intake_toggle != 2){
        intake_toggle = 2;
    }
    else {
        intake_toggle = 0;
    }
    wait(.3, seconds);
}

if (Controller1.ButtonUp.pressing()){
    intake_toggle = 0;
    wait(.3, seconds);
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

void activateoutake(){

if (Controller1.ButtonR2.pressing()){
    outake.spin(forward);
    outake.setVelocity(100, percent);
    // Brain.Screen.clearScreen();  
    // Brain.Screen.setCursor(10,10);
    // Brain.Screen.print("working");  
}
else {
    outake.stop();
    outake.setStopping(coast);
}

}
using namespace vex;  