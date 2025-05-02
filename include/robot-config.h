using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor RF;
extern motor RM;
extern motor RR;
extern motor LF;
extern motor LM;
extern motor LR; 
extern motor_group left_chassis;
extern motor_group right_chassis;
extern motor_group scoring_system;
extern controller Controller1;
extern inertial inertial_main;
extern inertial inertial_2;
extern inertial inertial_4;
extern inertial inertial_3;
extern aivision AIvision;
extern digital_out pneumaticA;
extern digital_out pneumaticC;
extern digital_out pneumaticG;
extern digital_out pneumaticH;
extern digital_out pneumaticE;
extern digital_out pneumaticF;
extern motor side_stakes;
extern motor flex_wheel;
extern motor hook_chain;
extern rotation tw;
extern rotation twh;
extern rotation arm;
extern optical op;
extern distance d1;
extern distance d2;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );