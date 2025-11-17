#ifndef DRIVE_H
#define DRIVE_H

#include "vex.h"

// Deadband function: sets input to 0 if it's below a certain threshold
float deadband(float input, float width);

// Converts a percentage to volts
float to_volt(float percent);

// Drive function: controls motors based on controller input
void drive();

// Optional: global throttle variables (you can also move these inside drive() if preferred)
extern float leftthrottle;
extern float rightthrottle;

#endif // DRIVE_H
