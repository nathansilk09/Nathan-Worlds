#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;
 
// A global instance of brain used for printing to the V5 Brain screen 
brain  Brain; 
motor RF = motor(PORT1, ratio6_1, false);
motor RM = motor(PORT2, ratio6_1, false); 
motor RR = motor(PORT3, ratio6_1, false);  
motor LF = motor(PORT11, ratio6_1, true);
motor LM = motor(PORT12, ratio6_1, true); 
motor LR = motor(PORT13, ratio6_1, true);
motor_group left_chassis = motor_group(LF, LM, LR);
motor_group right_chassis = motor_group(RF, RM, RR);
controller Controller1 = controller(primary); 
inertial inertial_main = inertial(PORT2);
motor intake = motor(PORT9, ratio18_1, false);



// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
