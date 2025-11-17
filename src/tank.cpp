#include <cmath>
                 
#include "vex.h"
#include "tank.h"

using namespace vex;  

// If input is below min width set it to zero
float deadband(float input, float width){                 
  if (fabs(input)<width){                 
    return(0);                 
  }                 
  return(input);                 
}   

// Convert a percentage to a voltage
float to_volt(float percent){                 
  return(percent*12.0/100.0);                 
}    

float leftthrottle = deadband(controller(primary).Axis3.value(), 5);
float rightthrottle = deadband(controller(primary).Axis2.value(), 5);

void drive() {

    if (!Controller1.ButtonL2.pressing() && !Controller1.ButtonA.pressing()){

        right_chassis.spin(fwd, to_volt(rightthrottle), volt);
        left_chassis.spin(fwd, to_volt(leftthrottle), volt);

    }

    else if (Controller1.ButtonL2.pressing() && !Controller1.ButtonA.pressing()){

        right_chassis.spin(fwd, to_volt(rightthrottle), volt);
        left_chassis.spin(fwd, to_volt(leftthrottle), volt);

    }

    else {

        left_chassis.stop();
        right_chassis.stop();

    }

    if(Controller1.ButtonA.pressing()){

        right_chassis.setStopping(hold);
        left_chassis.setStopping(hold);

    }

    else {
   
        left_chassis.setStopping(coast);
        right_chassis.setStopping(coast);

    } 
}