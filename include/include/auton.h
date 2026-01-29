#include "vex.h"

void drive_with_percent(float leftPercent, float rightPercent);
void drawButtons();
void drawButtons_Red();
void drawButtons_Blue();
void autonSelector();
void pre_auton();
void drive_with_voltage(float leftVoltage, float rightVoltage);
float reduce_0_to_360(float angle);
float reduce_negative_180_to_180(float angle);
float clamp(float input, float min, float max);
float to_percent(float volt);
float get_left_position_in();
float get_right_position_in();
float get_average_position_in();
float get_absolute_heading();
float compute(float error);
void is_finished();
void drive(float inches);
void drive_with_target(float inches, float angle);
void right_swing(float sdegrees);
void left_swing(float sdegrees);
void cust_left_swing(float sdegrees, float mult);
void cust_right_swing(float sdegrees, float mult);
extern int autonSelection;
void turn(float tdegrees);

extern float drive_timeout;
extern float drive_max_voltage;
extern float heading_max_voltage;
extern float drive_kp;