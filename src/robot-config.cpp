#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;
 
// A global instance of brain used for printing to the V5 Brain screen 
brain  Brain; 
motor side_stakes = motor(PORT15, ratio18_1, false);
motor flex_wheel = motor(PORT3, ratio6_1, true);
motor hook_chain = motor(PORT1, ratio6_1, true);
digital_out pneumaticA = digital_out(Brain.ThreeWirePort.B);
digital_out pneumaticC = digital_out(Brain.ThreeWirePort.C);
digital_out pneumaticH = digital_out(Brain.ThreeWirePort.D);
digital_out pneumaticG = digital_out(Brain.ThreeWirePort.G);
digital_out pneumaticE = digital_out(Brain.ThreeWirePort.E);
digital_out pneumaticF = digital_out(Brain.ThreeWirePort.F);
motor RF = motor(PORT13, ratio6_1, false);
motor RM = motor(PORT12, ratio6_1, false); 
motor RR = motor(PORT11, ratio6_1, false);  
motor LF = motor(PORT10, ratio6_1, true);
motor LM = motor(PORT9, ratio6_1, true); 
motor LR = motor(PORT8, ratio6_1, true);
rotation tw = rotation(PORT20);
rotation twh = rotation(PORT19);
rotation arm = rotation(PORT7);
optical op = optical(PORT18);
motor_group left_chassis = motor_group(LF, LM, LR);
motor_group scoring_system = motor_group(flex_wheel, hook_chain);
motor_group right_chassis = motor_group(RF, RM, RR);
controller Controller1 = controller(primary); 
inertial inertial_main = inertial(PORT2);
inertial inertial_2 = inertial(PORT6);
inertial inertial_3 = inertial(PORT4);
inertial inertial_4 = inertial(PORT2);
distance d1 = distance(PORT17);
distance d2 = distance(PORT6);


// color descriptions
aivision::colordesc COL1(1,     193,      53,     104,   10.00,    0.20);
aivision::colordesc COL2(2,      37,     196,     168,   10.00,    0.20);
aivision::colordesc COL3(3,      35,     137,     248,   10.00,    0.20);

// create an aivision instance
aivision AIvision( PORT17, COL1, COL2, COL3 );

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
