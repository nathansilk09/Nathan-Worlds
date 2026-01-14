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
extern controller Controller1;
extern inertial inertial_main;
extern inertial inertial_2;
extern inertial inertial_4;
extern inertial inertial_3;
extern motor intake;
extern motor outake;
extern digital_out PA;
extern digital_out PB;



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );