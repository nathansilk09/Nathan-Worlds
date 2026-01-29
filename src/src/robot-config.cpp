#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;
 
// A global instance of brain used for printing to the V5 Brain screen 
brain  Brain; 
motor LF = motor(PORT1, ratio6_1, false);
motor LM = motor(PORT2, ratio6_1, false); 
motor LR = motor(PORT3, ratio6_1, false);  
motor RF = motor(PORT11, ratio6_1, true);
motor RM = motor(PORT12, ratio6_1, true); 
motor RR = motor(PORT13, ratio6_1, true);
motor_group right_chassis = motor_group(LF, LM, LR);
motor_group left_chassis = motor_group(RF, RM, RR);
controller Controller1 = controller(primary); 
inertial inertial_main = inertial(PORT18);
motor intake = motor(PORT20, ratio18_1, false);
motor outake_pt1 = motor(PORT19, ratio18_1, true);
motor outake_pt2 = motor(PORT16, ratio18_1, false);
motor_group outake = motor_group(outake_pt1, outake_pt2);
digital_out PA = digital_out(Brain.ThreeWirePort.A);
digital_out PB = digital_out(Brain.ThreeWirePort.C);


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
