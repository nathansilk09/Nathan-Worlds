/*----------------------------------------------------------------------------*/                 
/*                                                                            */                 
/*    Module:       main.cpp                                                  */                 
/*    Author:       Student                                                   */                 
/*    Created:      3/12/2024, 2:22:38 PM                                     */                 
/*    Description:  V5 project                                                */                 
/*                                                                            */                 
/*----------------------------------------------------------------------------*/                 
                 
#include "vex.h"                 
#include <cmath>
                 
using namespace vex;          
                 
// A global instance of competition                 
competition Competition;                 
                 
// define your global instances of motors and other devices here                 
                 
/*---------------------------------------------------------------------------*/                 
/*                          Pre-Autonomous Functions                         */                 
/*                                                                           */                 
/*  You may want to perform some actions before the competition starts.      */                 
/*  Do them in the following function.  You must return from this function   */                 
/*  or the autonomous and usercontrol tasks will not be started.  This       */                 
/*  function is only called once after the V5 has been powered on and        */                 
/*  not every time that the robot is disabled.                               */                 
/*---------------------------------------------------------------------------*/                 


void drive_with_percent(float leftPercent, float rightPercent) {                 
                  
  left_chassis.spin(fwd, leftPercent, percent);                 
  right_chassis.spin(fwd, rightPercent, percent);                 
                 
}   

int autonSelection = 1; // Default to Auton 1

// Function to draw buttons
void drawButtons() {
    Brain.Screen.clearScreen();
    
    // Draw button rectangles
    Brain.Screen.setFillColor(vex::color::blue);
    Brain.Screen.drawRectangle(10, 50, 100, 50); // Button 1
    Brain.Screen.setFillColor(vex::color::red);
    Brain.Screen.drawRectangle(130, 50, 100, 50); // Button 2
    Brain.Screen.setFillColor(vex::color::red);
    Brain.Screen.drawRectangle(250, 50, 100, 50); // Button 3
    Brain.Screen.setFillColor(vex::color::blue);
    Brain.Screen.drawRectangle(370, 50, 100, 50); // Button 4

    // Print labels
    Brain.Screen.setFillColor(vex::color::black); // Reset fill color
    Brain.Screen.setPenColor(vex::color::white);  // White text
    Brain.Screen.printAt(35, 80, "Ring");
    Brain.Screen.printAt(155, 80, "Ring");
    Brain.Screen.printAt(275, 80, "Stake");
    Brain.Screen.printAt(395, 80, "Stake");

}

void drawButtons_Red() {
    Brain.Screen.clearScreen();
    
    // Draw button rectangles
    Brain.Screen.setFillColor(vex::color::red);
    Brain.Screen.drawRectangle(10, 50, 100, 50); // Button 1
    Brain.Screen.setFillColor(vex::color::red);
    Brain.Screen.drawRectangle(130, 50, 100, 50); // Button 2
    Brain.Screen.setFillColor(vex::color::red);
    Brain.Screen.drawRectangle(250, 50, 100, 50); // Button 3
    Brain.Screen.setFillColor(vex::color::red);
    Brain.Screen.drawRectangle(370, 50, 100, 50); // Button 4

    // Print labels
    Brain.Screen.setFillColor(vex::color::black); // Reset fill color
    Brain.Screen.setPenColor(vex::color::white);  // White text
    Brain.Screen.printAt(35, 80, "Both");
    Brain.Screen.printAt(155, 80, "No_Alliance");
    Brain.Screen.printAt(275, 80, "No_Ring");
    Brain.Screen.printAt(395, 80, "No_Both");

}

void drawButtons_Blue() {
    Brain.Screen.clearScreen();
    
    // Draw button rectangles
    Brain.Screen.setFillColor(vex::color::blue);
    Brain.Screen.drawRectangle(10, 50, 100, 50); // Button 1
    Brain.Screen.setFillColor(vex::color::blue);
    Brain.Screen.drawRectangle(130, 50, 100, 50); // Button 2
    Brain.Screen.setFillColor(vex::color::blue);
    Brain.Screen.drawRectangle(250, 50, 100, 50); // Button 3
    Brain.Screen.setFillColor(vex::color::blue);
    Brain.Screen.drawRectangle(370, 50, 100, 50); // Button 4

    // Print labels
    Brain.Screen.setFillColor(vex::color::black); // Reset fill color
    Brain.Screen.setPenColor(vex::color::white);  // White text
    Brain.Screen.printAt(35, 80, "Both");
    Brain.Screen.printAt(155, 80, "No_Alliance");
    Brain.Screen.printAt(275, 80, "No_Ring");
    Brain.Screen.printAt(395, 80, "No_Both");

}

// Function to detect button presses
void autonSelector() {
    int stage = 0; // 0 = choose alliance, 1 = choose specific auton
    drawButtons();
    bool selectionMade = false;

    while (!selectionMade) {
        if (Brain.Screen.pressing()) {
            int x = Brain.Screen.xPosition();
            int y = Brain.Screen.yPosition();

            if (y > 50 && y < 100) { // Main row
                if (stage == 0) {
                    if (x > 10 && x < 110) {
                        drawButtons_Blue(); stage = 1;
                    } else if (x > 130 && x < 230) {
                        drawButtons_Red(); stage = 2;
                    } else if (x > 250 && x < 350) {
                        drawButtons_Red(); stage = 3;
                    } else if (x > 370 && x < 470) {
                        drawButtons_Blue(); stage = 4;
                    }
                    wait(300, msec);
                } else {
                    // Now in second selection stage
                    if (x > 10 && x < 110) autonSelection = (stage - 1) * 4 + 1;
                    else if (x > 130 && x < 230) autonSelection = (stage - 1) * 4 + 2;
                    else if (x > 250 && x < 350) autonSelection = (stage - 1) * 4 + 3;
                    else if (x > 370 && x < 470) autonSelection = (stage - 1) * 4 + 4;

                    Brain.Screen.clearScreen();
                    Brain.Screen.setCursor(2, 2);
                    Brain.Screen.print("Auton Locked: %d", autonSelection);
                    selectionMade = true;
                    
                }
            }
        }
        wait(50, msec);
    }
}

void pre_auton() {
    vexcodeInit();
    inertial_main.calibrate();
    while (inertial_main.isCalibrating()) {
        wait(100, msec);
    }
    inertial_main.setHeading(0, degrees);
    inertial_main.setRotation(0, degrees);
    pneumaticG.set(true);
    pneumaticA.set(true);

    autonSelector(); // Run selector using Brain screen
}

// Spin both sides at set voltage
void drive_with_voltage(float leftVoltage, float rightVoltage) {                 
                  
  left_chassis.spin(fwd, leftVoltage, volt);                 
  right_chassis.spin(fwd, rightVoltage, volt);                 
                 
}     

// Set an angle to within the unit circle 
float reduce_0_to_360(float angle) {                 
  while(!(angle >= 0 && angle < 360)) {                 
    if( angle < 0 ) { angle += 360; }                 
    if(angle >= 360) { angle -= 360; }                 
  }                 
  return(angle);                 
}                 

// Convert an angle from -180 to 180 degrees            
float reduce_negative_180_to_180(float angle) {                 
  while(!(angle >= -180 && angle < 180)) {                 
    if( angle < -180 ) { angle += 360; }                 
    if(angle >= 180) { angle -= 360; }                 
  }                 
  return(angle);                 
}                 

// Clamp a number to the desired min/max
float clamp(float input, float min, float max){                 
  if( input > max ){ return(max); }                 
  if(input < min){ return(min); }                 
  return(input);                 
}                 
                 
// Convert a percentage to a voltage
float to_volt(float percent){                 
  return(percent*12.0/100.0);                 
}    

float to_percent(float volt){                 
  return(volt/12.0*100.0);                 
}    

// If input is below min width set it to zero
float deadband(float input, float width){                 
  if (fabs(input)<width){                 
    return(0);                 
  }                 
  return(input);                 
}                 

float distance_sense_width = 9; // Width between distance sensors

// Convert distance sensor values to an angle
float distance_angle() {
  return(90-(atan((distance_sense_width)/(d1.objectDistance(inches) - d2.objectDistance(inches)))));
}


float wheel_ratio = 0.75; // Gear ratio      
float wheel_diameter = 3.25;      
float drive_multiplier = 0.75/360.0*M_PI*wheel_diameter; // Converts degrees rotated on drive chassis to inches travelled 
float tw_drive_multiplier = 1/360.0*M_PI*2; // Converts degrees rotated on tracking wheel to inches travelled               
float accumulated_error = 0; // Error integral                
float previous_error = 0;             
float average_position;                 
float start_average_position;                 
float PID_value;                 
float target;                 
float desired_heading; // Target heading                
float time_spent_running;                 
float time_spent_settled;   
float heading_accumulated_error = 0;                 
float heading_previous_error = 0;  
float arm_accumulated_error = 0;                 
float arm_previous_error = 0;  
float output; // PID computed number   
float arminput;
float arm_degs;         
                 
bool finished = false; // Has the robot reached the target??         
                 
float drive_max_voltage = 12;                 
float drive_kp = .7;                 
float drive_ki = 0;                 
float drive_kd = 4;                 
float drive_starti = 15;                 
float drive_settle_error = 1;                 
float drive_settle_time = 10;                 
float drive_timeout = 2000;   

float arm_max_voltage = 12;
float arm_kp = .2;                 
float arm_ki = 0;                 
float arm_kd = 0;                 
float arm_starti = 10000;                 
float arm_settle_error = 2;                 
float arm_settle_time = 100;                 
float arm_timeout = 100000;   
float y = 0;
                 
float turn_max_voltage = 12;                 
float turn_kp = .37;                 
float turn_ki = 0.003;                 
float turn_kd = 3;                 
float turn_starti = 1000;                 
float turn_settle_error = 1;                 
float turn_settle_time = 10;                 
float turn_timeout = 400000;                 
                 
float swing_max_voltage = 12;                 
float swing_kp = .8;                
float swing_ki = .003;                 
float swing_kd = 4;                 
float swing_starti = 15;                 
float swing_settle_error = 5;                 
float swing_settle_time = 30;                 
float swing_timeout = 4000;                 
                 
float heading_max_voltage = 3;                 
float heading_kp = .3;                 
float heading_ki = 0;                 
float heading_kd = 1;                 
float heading_starti = 15;                                 
                 
float base_max_voltage = 6; // Max voltage allowed               
float base_kp = 0; // Controls decelaration                
float base_ki = 0; // Controls accelaration           
float base_kd = 0; // Counteracts oscillation                
float base_starti = 15; // Where 'i' starts to kick in it              
float base_settle_error = 2; // Amount of allowed error for the robot to settle in             
float base_settle_time = 100; // Amount of time robot needs to be within settle error before it finishes
float base_timeout = 4000;  

float previous_twa = 0; // Previous tracking wheel
int twm = 0; // Tracking wheel rotations
float x = 0; // Flexible variable usually used for time
int opponent = 10; // Oppenent colour (blue, 200 ; red, 10)

float b = 0; // Time variable used to measure time after detecting a ring (blue)
float r = 0; // Time variable used to measure time after detecting a ring (red)
bool boolb = false; // If optical sensor detects blue ring
bool boolr = false; // If optical sensor detects red ring
bool boolbd = false; // If distance sensor detects blue ring
bool boolrd = false; // If distance sensor detects red ring


// Updates tracking wheel position
float trackingwheel(){                 
                
  return((tw.angle()+(360*twm))*tw_drive_multiplier);   

}   

// Updates left chassis position
float get_left_position_in() {                 
                 
  return(left_chassis.position(degrees)*drive_multiplier);                 
                 
}                 

// Updates right chassis position
float get_right_position_in() {                 
                 
  return(right_chassis.position(degrees)*drive_multiplier);                 
                 
}                 

// Takes an error value and converts it to a outputted PID number
float compute(float error) {                 

  // Calculates the 'i' value              
  if (error <= base_starti) {                 

    if (error>0) {

      accumulated_error += 10;                 

    }  

    else {

      accumulated_error -= 10;                 

    }          

                 
  }                 

  // Resets 'i' to zero if it crosses the target          
  if (error*previous_error < 0) {                 
                 
    accumulated_error = 0;                 
                 
  }            
        
  PID_value = base_kp*error + base_ki*accumulated_error + base_kd*(error-previous_error); // Calculates PID value              
  previous_error = error; // Updates previous error                
  time_spent_running += 10; // Updates time the loop has spent running     
  
  // Updates time robot has spent in target
  if (fabs(error) <= base_settle_error) {                 
                 
    time_spent_settled += 10;                
                 
  }                             
  else {                 
                 
    time_spent_settled = 0;                 
                 
  }                 
                 
  return(PID_value);                 
                 
}                 


void is_finished() {                 
                 
  if (time_spent_settled >= base_settle_time) {                 
                 
    finished = true;                 
                 
  }                 
                 
  else if (time_spent_running >= base_timeout) {                 
                 
    finished = true;                 
                 
  }                 
                 
  else {                 
                 
    finished = false;                 
                 
  }                 
                 
}                 

float bd = 0;
float rd = 0; 

float hook_kill = 0;
bool boolhook = false;
bool cexecutive = false;
bool texecutive = false;
float hook_kill_check = 0;
bool torque_pro = false;
bool chainkill = false;

// Intake with colour sort
void intake_exclude(int hue, bool sleep) {
  
  op.setLight(vex::ledState::on);
  op.setLightPower(100, percent);

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(op.hue());
  
  // Checks for red ring
  if (op.hue() <= 20) {
    boolrd = true;
  }

  // Checks for blue ring
  if (op.hue() > 200) {
    boolbd = true;
  }

  // Distance sensor + red ring
  if (boolrd && rd >= .03) {
     if (d1.objectDistance(inches) < 3){
      boolr = true;
     }
  }

  // Distance sensor + blue ring
  if (boolbd) {
    if (d1.objectDistance(inches) < 3){
      boolb = true;
    }
  }
   
  // Time since red ring crossed distance sensor
  if (boolr == true){
    r += .01;
  }

  // Time since blue ring crossed distance sensor
  if (boolb == true){
    b += .01;
  }

  // Time since red ring crossed optical sensor
  if (boolrd == true){
    rd += .01;
  }

  // Time since blue ring crossed optical sensor
  if (boolbd == true){
    bd += .01;
  }

  // Resets r/b to zero after certain amount of time
  if (r >= .35 or b >= .35){
    boolbd = false; boolrd = false; b = 0; r = 0; boolr = false; boolb = false; bd = 0; rd = 0;
  }

  // Intake exclude , blue
  if (hue == 200){
    if (b <= .04) {
      if (!texecutive) {
        hook_chain.spin(fwd, -12, volt);
      }
      flex_wheel.spin(fwd, -12, volt);
      cexecutive = false;
      op.setLight(ledState::on);
      op.setLightPower(100, percent);
    }
    else {
      scoring_system.stop();
      cexecutive = true;
    }
  }

  // Intake exclude , red
  else {
    if (r <= .04) {
      if (!texecutive) {
        hook_chain.spin(fwd, -12, volt);
      }
      flex_wheel.spin(fwd, -12, volt);
      cexecutive = false;
      op.setLight(ledState::on);
      op.setLightPower(100, percent);
    }
    else {
      scoring_system.stop();
      cexecutive = true;
    }
  }

  if (!cexecutive) {
    if (hook_kill <= .1) {
      texecutive = false;
    } 
    else {
      hook_chain.spin(fwd, 12, volt);     
      texecutive = true; 
    }
  }


  if (hook_chain.torque() > .30) {
    hook_kill_check += .01;
  }
  else {
    hook_kill_check = 0;
  }


  if (hook_kill_check >= .7){
    torque_pro = true;
  }

  if (torque_pro){
    hook_kill += .01;
  }

  if (hook_kill >= .8) {
    hook_kill = 0;
    torque_pro = false;
  }
  
  if (hook_kill < 0) {
    hook_kill = 0;
  }
  
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(20, 20);
  Brain.Screen.print(hook_chain.torque());

  if(chainkill){
    hook_chain.stop();
    hook_chain.setStopping(coast);
  }

  // If void is not in a void that's already sleeping this will give the code a break
  if (sleep) {
    vex::task::sleep(10);
  }

}

// Intake with colour sort
void nazi_intake(int hue, bool sleep) {
  
  op.setLight(vex::ledState::on);
  op.setLightPower(100, percent);

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(op.hue());
  
  // Checks for red ring
  if (op.hue() <= 20) {
    boolrd = true;
  }

  // Checks for blue ring
  if (op.hue() > 200) {
    boolbd = true;
  }

  if(boolbd or boolrd){
    hook_chain.stop();
    flex_wheel.spin(fwd, 12, volt);
  }
  else {
    scoring_system.spin(fwd, -12, volt);  
  }


  // If void is not in a void that's already sleeping this will give the code a break
  if (sleep) {
    vex::task::sleep(10);
  }

}

void ultra_nazi_intake(int hue, bool sleep) {
  
  if (d1.objectDistance(inches) < 3){
    scoring_system.stop();
  }
  else {
    scoring_system.spin(fwd, -12, volt);  
  }

}


void nazi_intake_opp(int hue, bool sleep) {
  
  op.setLight(vex::ledState::on);
  op.setLightPower(100, percent);

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(op.hue());
  
  // Checks for red ring
  if (op.hue() <= 20) {
    boolrd = true;
  }

  // Checks for blue ring
  if (op.hue() > 200) {
    boolbd = true;
  }

  if (opponent == 200){
    if(boolbd){
      if(!chainkill){ hook_chain.spin(fwd, 12, volt); }
      flex_wheel.spin(fwd, 12, volt);
    }
    else {
      if(!chainkill){ hook_chain.spin(fwd, -12, volt); }
      flex_wheel.spin(fwd, -12, volt);  
    }
  }
  else{
    if(boolrd){
      if(!chainkill){ hook_chain.spin(fwd, 12, volt); }
      flex_wheel.spin(fwd, 12, volt);
    }
    else {
      if(!chainkill){ hook_chain.spin(fwd, -12, volt); }
      flex_wheel.spin(fwd, -12, volt);  
    }
  }


  // If void is not in a void that's already sleeping this will give the code a break
  if (sleep) {
    vex::task::sleep(10);
  }

}

// Runs the intake with no chain
void intake_exclude_no_chain(int hue, bool sleep) {
  
  flex_wheel.spin(fwd, -12, volt);
  hook_chain.stop();
  if (sleep) {
    vex::task::sleep(10);
  }

}

// Inertial sensor vakue
float inert1;

// Gets a heading value between 0 and 360
float get_absolute_heading() {                 
                 
  inert1 = reduce_0_to_360(inertial_main.heading());          
  return(inert1);

} 
    
// Drives in a straight line a given distance
void drive(float inches, bool intake_auton) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  start_average_position = trackingwheel();                 
  float average_position = start_average_position;                 
  desired_heading = reduce_0_to_360(get_absolute_heading());                 
  float distance = -inches; // Distance robot will be driving               
  base_max_voltage = drive_max_voltage;                 
  base_kd = drive_kd;                 
  base_ki = drive_ki;                 
  base_kp = drive_kp;                 
  base_starti = drive_starti;                 
  base_settle_error = drive_settle_error;                 
  base_settle_time = drive_settle_time;                 
  base_timeout = drive_timeout;                 
  previous_twa = tw.angle();
  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;  

  // All of that is just effectively resetting values and making sure the PID values matches the drive PID values 

  // Start of the loop     
  while (!finished) {                 
    
    // Updates tracking wheel rotations
    if(previous_twa - tw.angle() > 100) {

      twm += 1;

    }          
    else if (previous_twa - tw.angle() < -100) {

      twm += -1;

    }   

    previous_twa = tw.angle();                 
    average_position = trackingwheel();        
    float drive_error = distance + start_average_position - average_position; // Distance to the target           
    float heading_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Amount inertial sensor has been thrown off            
    float drive_output = compute(drive_error); // PID'ed number
    is_finished(); // Checks if it can cut out the loop

    // Updates heading PID values
    if (heading_error <= heading_starti) {                                  
      heading_accumulated_error += 10;                                  
    }                          
    if (heading_error*heading_previous_error < 0) {                                
      heading_accumulated_error = 0;                                
    }                                   
    float heading_output = heading_kp*heading_error + heading_ki*heading_accumulated_error + heading_kd*(heading_error-heading_previous_error);                 
    heading_previous_error = heading_error; 

    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage); // Clamps drive voltage
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage); // Clamps heading voltage
                    
    drive_with_voltage((drive_output + heading_output), (drive_output - heading_output)); // Drives with calculated voltages

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      intake_exclude(opponent, false);        
    }
    vex::task::sleep(10);                 
                 
  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();                 
                 
}     

// Drives in a straight line a given distance
void ultra_nazi_drive(float inches, bool intake_auton) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  start_average_position = trackingwheel();                 
  float average_position = start_average_position;                 
  desired_heading = reduce_0_to_360(get_absolute_heading());                 
  float distance = -inches; // Distance robot will be driving               
  base_max_voltage = drive_max_voltage;                 
  base_kd = drive_kd;                 
  base_ki = drive_ki;                 
  base_kp = drive_kp;                 
  base_starti = drive_starti;                 
  base_settle_error = drive_settle_error;                 
  base_settle_time = drive_settle_time;                 
  base_timeout = drive_timeout;                 
  previous_twa = tw.angle();
  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;  

  // All of that is just effectively resetting values and making sure the PID values matches the drive PID values 

  // Start of the loop     
  while (!finished) {                 
    
    // Updates tracking wheel rotations
    if(previous_twa - tw.angle() > 100) {

      twm += 1;

    }          
    else if (previous_twa - tw.angle() < -100) {

      twm += -1;

    }   

    previous_twa = tw.angle();                 
    average_position = trackingwheel();        
    float drive_error = distance + start_average_position - average_position; // Distance to the target           
    float heading_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Amount inertial sensor has been thrown off            
    float drive_output = compute(drive_error); // PID'ed number
    is_finished(); // Checks if it can cut out the loop

    // Updates heading PID values
    if (heading_error <= heading_starti) {                                  
      heading_accumulated_error += 10;                                  
    }                          
    if (heading_error*heading_previous_error < 0) {                                
      heading_accumulated_error = 0;                                
    }                                   
    float heading_output = heading_kp*heading_error + heading_ki*heading_accumulated_error + heading_kd*(heading_error-heading_previous_error);                 
    heading_previous_error = heading_error; 

    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage); // Clamps drive voltage
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage); // Clamps heading voltage
                    
    drive_with_voltage((drive_output + heading_output), (drive_output - heading_output)); // Drives with calculated voltages

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      ultra_nazi_intake(opponent, false);        
    }
    vex::task::sleep(10);                 
                 
  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();                 
                 
}    

// Drives in a straight line a given distance
void drive_chain_cutout(float inches, float chainout, bool intake_auton) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  start_average_position = trackingwheel();                 
  float average_position = start_average_position;                 
  desired_heading = reduce_0_to_360(get_absolute_heading());                 
  float distance = -inches; // Distance robot will be driving               
  base_max_voltage = drive_max_voltage;                 
  base_kd = drive_kd;                 
  base_ki = drive_ki;                 
  base_kp = drive_kp;                 
  base_starti = drive_starti;                 
  base_settle_error = drive_settle_error;                 
  base_settle_time = drive_settle_time;                 
  base_timeout = drive_timeout;                 
  previous_twa = tw.angle();
  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;  
  chainkill = false; 

  // All of that is just effectively resetting values and making sure the PID values matches the drive PID values 

  // Start of the loop     
  while (!finished) {                 
    
    // Updates tracking wheel rotations
    if(previous_twa - tw.angle() > 100) {

      twm += 1;

    }          
    else if (previous_twa - tw.angle() < -100) {

      twm += -1;

    }   

    previous_twa = tw.angle();                 
    average_position = trackingwheel();        
    float drive_error = distance + start_average_position - average_position; // Distance to the target           
    float heading_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Amount inertial sensor has been thrown off            
    float drive_output = compute(drive_error); // PID'ed number
    is_finished(); // Checks if it can cut out the loop

    // Updates heading PID values
    if (heading_error <= heading_starti) {                                  
      heading_accumulated_error += 10;                                  
    }                          
    if (heading_error*heading_previous_error < 0) {                                
      heading_accumulated_error = 0;                                
    }    

    if (time_spent_running >= chainout * 1000){
      chainkill = true;
    } 

    float heading_output = heading_kp*heading_error + heading_ki*heading_accumulated_error + heading_kd*(heading_error-heading_previous_error);                 
    heading_previous_error = heading_error; 

    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage); // Clamps drive voltage
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage); // Clamps heading voltage
                    
    drive_with_voltage((drive_output + heading_output), (drive_output - heading_output)); // Drives with calculated voltages

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      nazi_intake_opp(opponent, false);        
    }

    if(chainkill) {
      hook_chain.stop();
      hook_chain.setStopping(coast);
    }
    
    vex::task::sleep(10);                 
                 
  }                 

  chainkill = false;   
  left_chassis.stop();                 
  right_chassis.stop();                 
                 
}    

// Drives in a straight line a given distance
void nazi_drive(float inches, bool intake_auton) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  start_average_position = trackingwheel();                 
  float average_position = start_average_position;                 
  desired_heading = reduce_0_to_360(get_absolute_heading());                 
  float distance = -inches; // Distance robot will be driving               
  base_max_voltage = drive_max_voltage;                 
  base_kd = drive_kd;                 
  base_ki = drive_ki;                 
  base_kp = drive_kp;                 
  base_starti = drive_starti;                 
  base_settle_error = drive_settle_error;                 
  base_settle_time = drive_settle_time;                 
  base_timeout = drive_timeout;                 
  previous_twa = tw.angle();
  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;  

  // All of that is just effectively resetting values and making sure the PID values matches the drive PID values 

  // Start of the loop     
  while (!finished) {                 
    
    // Updates tracking wheel rotations
    if(previous_twa - tw.angle() > 100) {

      twm += 1;

    }          
    else if (previous_twa - tw.angle() < -100) {

      twm += -1;

    }   

    previous_twa = tw.angle();                 
    average_position = trackingwheel();        
    float drive_error = distance + start_average_position - average_position; // Distance to the target           
    float heading_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Amount inertial sensor has been thrown off            
    float drive_output = compute(drive_error); // PID'ed number
    is_finished(); // Checks if it can cut out the loop

    // Updates heading PID values
    if (heading_error <= heading_starti) {                                  
      heading_accumulated_error += 10;                                  
    }                          
    if (heading_error*heading_previous_error < 0) {                                
      heading_accumulated_error = 0;                                
    }                                   
    float heading_output = heading_kp*heading_error + heading_ki*heading_accumulated_error + heading_kd*(heading_error-heading_previous_error);                 
    heading_previous_error = heading_error; 

    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage); // Clamps drive voltage
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage); // Clamps heading voltage
                    
    drive_with_voltage((drive_output + heading_output), (drive_output - heading_output)); // Drives with calculated voltages

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      nazi_intake(opponent, false);        
    }
    vex::task::sleep(10);                 
                 
  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();                 
                 
}    

void drive_with_arm(float inches, bool intake_auton) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  start_average_position = trackingwheel();                 
  float average_position = start_average_position;                 
  desired_heading = reduce_0_to_360(get_absolute_heading());                 
  float distance = -inches; // Distance robot will be driving               
  base_max_voltage = drive_max_voltage;                 
  base_kd = drive_kd;                 
  base_ki = drive_ki;                 
  base_kp = drive_kp;                 
  base_starti = drive_starti;                 
  base_settle_error = drive_settle_error;                 
  base_settle_time = drive_settle_time;                 
  base_timeout = drive_timeout;                 
  previous_twa = tw.angle();
  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;  

  // All of that is just effectively resetting values and making sure the PID values matches the drive PID values 

  // Start of the loop     
  while (!finished) {                 
    
    // Updates tracking wheel rotations
    if(previous_twa - tw.angle() > 100) {

      twm += 1;

    }          
    else if (previous_twa - tw.angle() < -100) {

      twm += -1;

    }   

    if (arm.angle() < 310 && arm.angle() > 100){
      side_stakes.spin(fwd, -6.8, volt);
    }
    else if (arm.angle() > 317 or arm.angle() < 100){
      side_stakes.spin(fwd, 6.8, volt);
    }
    else {
      side_stakes.stop();
    }


    previous_twa = tw.angle();                 
    average_position = trackingwheel();        
    float drive_error = distance + start_average_position - average_position; // Distance to the target           
    float heading_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Amount inertial sensor has been thrown off            
    float drive_output = compute(drive_error); // PID'ed number
    is_finished(); // Checks if it can cut out the loop

    // Updates heading PID values
    if (heading_error <= heading_starti) {                                  
      heading_accumulated_error += 10;                                  
    }                          
    if (heading_error*heading_previous_error < 0) {                                
      heading_accumulated_error = 0;                                
    }                                   
    float heading_output = heading_kp*heading_error + heading_ki*heading_accumulated_error + heading_kd*(heading_error-heading_previous_error);                 
    heading_previous_error = heading_error; 

    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage); // Clamps drive voltage
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage); // Clamps heading voltage
                    
    drive_with_voltage((drive_output + heading_output), (drive_output - heading_output)); // Drives with calculated voltages

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      intake_exclude(opponent, false);        
    }

    vex::task::sleep(10);                 
                 
  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();                 
                 
}   

// Drives in a straight line a given distance, but also clamps down after given time
void drive_with_clamp(float inches, bool intake_auton, float inpsec) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  start_average_position = trackingwheel();                 
  float average_position = start_average_position;                 
  desired_heading = reduce_0_to_360(get_absolute_heading());                 
  float distance = -inches; // Distance robot will be driving               
  base_max_voltage = drive_max_voltage;                 
  base_kd = drive_kd;                 
  base_ki = drive_ki;                 
  base_kp = drive_kp;                 
  base_starti = drive_starti;                 
  base_settle_error = drive_settle_error;                 
  base_settle_time = drive_settle_time;                 
  base_timeout = drive_timeout;                 
  previous_twa = tw.angle();
  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;  
  x = 0;

  // All of that is just effectively resetting values and making sure the PID values matches the drive PID values 

  // Start of the loop     
  while (!finished) {                 
    
    // Updates tracking wheel rotations
    if(previous_twa - tw.angle() > 100) {

      twm += 1;

    }          
    else if (previous_twa - tw.angle() < -100) {

      twm += -1;

    }   

    previous_twa = tw.angle();                 
    average_position = trackingwheel();        
    float drive_error = distance + start_average_position - average_position; // Distance to the target           
    float heading_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Amount inertial sensor has been thrown off            
    float drive_output = compute(drive_error); // PID'ed number
    is_finished(); // Checks if it can cut out the loop

    // Updates heading PID values
    if (heading_error <= heading_starti) {                                  
      heading_accumulated_error += 10;                                  
    }                          
    if (heading_error*heading_previous_error < 0) {                                
      heading_accumulated_error = 0;                                
    }                                   
    float heading_output = heading_kp*heading_error + heading_ki*heading_accumulated_error + heading_kd*(heading_error-heading_previous_error);                 
    heading_previous_error = heading_error; 

    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage); // Clamps drive voltage
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage); // Clamps heading voltage
                    
    drive_with_voltage(drive_output + heading_output, drive_output - heading_output); // Drives with calculated voltages

    // If loop has been running long enough robot will clamp down
    if (time_spent_running/1000 >= inpsec){
      pneumaticA.set(false);
    }

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      intake_exclude(opponent, false);        
    }
    vex::task::sleep(10);                 
                 
  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();                 
                 
}   

// Drives in a straight line a given distance
void drive_with_target(float inches, bool intake_auton, float angle) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  start_average_position = trackingwheel();                 
  float average_position = start_average_position;                 
  desired_heading = reduce_0_to_360(angle); // Sets desired angle to inputted angle              
  float distance = -inches; // Distance robot will be driving               
  base_max_voltage = drive_max_voltage;                 
  base_kd = drive_kd;                 
  base_ki = drive_ki;                 
  base_kp = drive_kp;                 
  base_starti = drive_starti;                 
  base_settle_error = drive_settle_error;                 
  base_settle_time = drive_settle_time;                 
  base_timeout = drive_timeout;                 
  previous_twa = tw.angle();
  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;  

  // All of that is just effectively resetting values and making sure the PID values matches the drive PID values 

  // Start of the loop     
  while (!finished) {                 
    
    // Updates tracking wheel rotations
    if(previous_twa - tw.angle() > 100) {

      twm += 1;

    }          
    else if (previous_twa - tw.angle() < -100) {

      twm += -1;

    }   

    previous_twa = tw.angle();                 
    average_position = trackingwheel();        
    float drive_error = distance + start_average_position - average_position; // Distance to the target           
    float heading_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Amount inertial sensor has been thrown off            
    float drive_output = compute(drive_error); // PID'ed number
    is_finished(); // Checks if it can cut out the loop

    // Updates heading PID values
    if (heading_error <= heading_starti) {                                  
      heading_accumulated_error += 10;                                  
    }                          
    if (heading_error*heading_previous_error < 0) {                                
      heading_accumulated_error = 0;                                
    }                                   
    float heading_output = heading_kp*heading_error + heading_ki*heading_accumulated_error + heading_kd*(heading_error-heading_previous_error);                 
    heading_previous_error = heading_error; 

    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage); // Clamps drive voltage
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage); // Clamps heading voltage
                    
    drive_with_voltage(drive_output + heading_output, drive_output - heading_output); // Drives with calculated voltages

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      intake_exclude(opponent, false);        
    }
    vex::task::sleep(10);                 
                 
  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();                 
                 
}   

//turns to given heading
void turn(float tdegrees, bool intake_auton) {                 

  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;                              
  desired_heading = tdegrees;                 
  base_max_voltage = turn_max_voltage;                 
  base_kd = turn_kd;                 
  base_ki = turn_ki;                 
  base_kp = turn_kp;                 
  base_starti = turn_starti;                 
  base_settle_error = turn_settle_error;                 
  base_settle_time = turn_settle_time;                 
  base_timeout = turn_timeout;   
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;               
                 
  // All of that is just effectively resetting values and making sure the PID values matches the turn PID values 
                 
  while (!finished) {                 
       
    float turn_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Calculates how far away the robot is from the target                               
    float turn_output = compute(turn_error); // Figures out the PID turn value

    turn_output = clamp(turn_output, -turn_max_voltage, turn_max_voltage); // Clamps drive voltage

    is_finished(); // Checks if turn is finished 

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      intake_exclude(opponent, false);        
    }      
    drive_with_voltage(turn_output, -turn_output); // Turns with calculated voltages
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop(); 
               
}    

//turns to given heading
void nazi_turn(float tdegrees, bool intake_auton) {                 

  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;                              
  desired_heading = tdegrees;                 
  base_max_voltage = turn_max_voltage;                 
  base_kd = turn_kd;                 
  base_ki = turn_ki;                 
  base_kp = turn_kp;                 
  base_starti = turn_starti;                 
  base_settle_error = turn_settle_error;                 
  base_settle_time = turn_settle_time;                 
  base_timeout = turn_timeout;   
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;               
                 
  // All of that is just effectively resetting values and making sure the PID values matches the turn PID values 
                 
  while (!finished) {                 
       
    float turn_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Calculates how far away the robot is from the target                               
    float turn_output = compute(turn_error); // Figures out the PID turn value

    turn_output = clamp(turn_output, -turn_max_voltage, turn_max_voltage); // Clamps drive voltage

    is_finished(); // Checks if turn is finished 

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      nazi_intake(opponent, false);        
    }      
    drive_with_voltage(turn_output, -turn_output); // Turns with calculated voltages
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop(); 
               
}  

// Swings one side to a given angle   
void right_swing(float sdegrees, bool intake_auton) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  desired_heading = sdegrees;                 
  base_max_voltage = swing_max_voltage;                 
  base_kd = swing_kd;                 
  base_ki = swing_ki;                 
  base_kp = swing_kp;                 
  base_starti = swing_starti;                 
  base_settle_error = swing_settle_error;                 
  base_settle_time = swing_settle_time;                 
  base_timeout = swing_timeout;        
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;          
                 
  // All of that is just effectively resetting values and making sure the PID values matches the swing PID values 
                 
  while (!finished) {                 
                 
    float swing_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Calculates how far away the robot is from the target                               
    float swing_output = compute(swing_error); // Figures out the PID turn value

    swing_output = clamp(swing_output, -swing_max_voltage, swing_max_voltage); // Clamps drive voltage

    is_finished(); // Checks if swing is finished 

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      intake_exclude(opponent, false);        
    }      
    drive_with_voltage(swing_output, 0); // Left swings with calculated voltages
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();
                 
}                 
                 
// Swings one side to a given angle   
void left_swing(float sdegrees, bool intake_auton) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  desired_heading = sdegrees;                 
  base_max_voltage = swing_max_voltage;                 
  base_kd = swing_kd;                 
  base_ki = swing_ki;                 
  base_kp = swing_kp;                 
  base_starti = swing_starti;                 
  base_settle_error = swing_settle_error;                 
  base_settle_time = swing_settle_time;                 
  base_timeout = swing_timeout;        
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;          
                 
  // All of that is just effectively resetting values and making sure the PID values matches the swing PID values 
                 
  while (!finished) {                 
                 
    float swing_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Calculates how far away the robot is from the target                               
    float swing_output = compute(swing_error); // Figures out the PID turn value

    swing_output = clamp(swing_output, -swing_max_voltage, swing_max_voltage); // Clamps drive voltage

    is_finished(); // Checks if swing is finished 

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      intake_exclude(opponent, false);        
    }      
    drive_with_voltage(0, -swing_output); // Left swings with calculated voltages
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();
                 
}     

// Swings one side to a given angle but the other side drives at a given mult of the other side  
void cust_left_swing(float sdegrees, bool intake_auton, float mult) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  desired_heading = sdegrees;                 
  base_max_voltage = swing_max_voltage;                 
  base_kd = swing_kd;                 
  base_ki = swing_ki;                 
  base_kp = swing_kp;                 
  base_starti = swing_starti;                 
  base_settle_error = swing_settle_error;                 
  base_settle_time = swing_settle_time;                 
  base_timeout = swing_timeout;        
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;          
                 
  // All of that is just effectively resetting values and making sure the PID values matches the swing PID values 
                 
  while (!finished) {                 
                 
    float swing_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Calculates how far away the robot is from the target                               
    float swing_output = compute(swing_error); // Figures out the PID turn value

    swing_output = clamp(swing_output, -swing_max_voltage, swing_max_voltage); // Clamps drive voltage

    is_finished(); // Checks if swing is finished 

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      intake_exclude(opponent, false);        
    }      
    drive_with_voltage(-swing_output*mult, -swing_output); // Left swings with calculated voltages
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();
                 
}    

// Swings one side to a given angle but the other side drives at a given mult of the other side  
void cust_right_swing(float sdegrees, bool intake_auton, float mult) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  desired_heading = sdegrees;                 
  base_max_voltage = swing_max_voltage;                 
  base_kd = swing_kd;                 
  base_ki = swing_ki;                 
  base_kp = swing_kp;                 
  base_starti = swing_starti;                 
  base_settle_error = swing_settle_error;                 
  base_settle_time = swing_settle_time;                 
  base_timeout = swing_timeout;        
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;          
                 
  // All of that is just effectively resetting values and making sure the PID values matches the swing PID values 
                 
  while (!finished) {                 
                 
    float swing_error = reduce_negative_180_to_180(desired_heading - get_absolute_heading()); // Calculates how far away the robot is from the target                               
    float swing_output = compute(swing_error); // Figures out the PID turn value

    swing_output = clamp(swing_output, -swing_max_voltage, swing_max_voltage); // Clamps drive voltage

    is_finished(); // Checks if swing is finished 

    // If intake_auton is true the robot will intake excluding opponents colour
    if (intake_auton){
      intake_exclude(opponent, false);        
    }      
    drive_with_voltage(swing_output, swing_output*mult);
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();
                 
}    


void texecute_wait (double time) {
  x = 0;
  while (x < time*1000) {
    x += 10;
    intake_exclude(opponent, true);
  }
}

/*---------------------------------------------------------------------------*/                 
/*                                                                           */                 
/*                              Autonomous Task                              */                 
/*                                                                           */                 
/*  This task is used to control your robot during the autonomous phase of   */                 
/*  a VEX Competition.                                                       */                 
/*                                                                           */                 
/*  You must modify the code to add your own robot specific commands here.   */                 
/*---------------------------------------------------------------------------*/                 

void autonomous(void) {                 
  
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(2, 2);
  Brain.Screen.print("Running Auton %d", autonSelection);

  switch (autonSelection) {

    case 100:
    // Blue ring    `
      turn_settle_time = 10; opponent = 10; drive_timeout = 600; wait(10, vex::timeUnits::msec); // Setting stuff
      drive_with_arm(-7, false); // Drive to stake, lift arm
      side_stakes.spin(fwd, -12, volt); wait(.2, seconds); side_stakes.setStopping(coast); pneumaticC.set(true); drive_timeout = 300; // Score preload, lift intake
      drive(4, true); side_stakes.stop(); drive_timeout = 900; // Drive away from stake
      turn(-43.5, true); // Turn to raised ring
      drive_max_voltage = 3; nazi_drive(12, true); drive_max_voltage = 12;  pneumaticC.set(false); // Pick up raised ring, drop intake
      drive_timeout = 1500; nazi_turn(-137, true); // Turn to stake
      nazi_drive(-22, true); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.4, true); // Align with centre
      turn(-41, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.5, false); pneumaticE.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); wait(.1, seconds); pneumaticC.set(false); pneumaticE.set(false); // Back out, drop intake, raise arm
      left_swing(48, true); // Swing into ring
      turn(52, true); // Turn to 4
      drive(5.1, true);   // Drive to 4
      swing_max_voltage = 12; cust_left_swing(90, true, .25); // Swing into 4
      turn(90, true); // Align
      drive_timeout = 400; drive_max_voltage = 10; drive(4, true); // D1 4
      drive(7, true); drive_max_voltage = 4; drive(8.5, true); drive_timeout = 1500; drive_max_voltage = 12; // D2 4
      cust_left_swing(57, true, .4); flex_wheel.spin(fwd, 12, volt); // Swing out of 4, reverse intake
      turn_timeout = 500; turn(115,  false); // Turn to final ring
      drive_timeout = 600; drive(13, true); drive(7, true); // Pick up final ring
      turn(95.5, true); // Turn to ladder
      drive_timeout = 1500; hook_chain.setStopping(coast); drive_kd = 9; drive_chain_cutout(-40, .5, true); // Drive into ladder
      break;

    case 3:
    // Blue ring with no ring
      turn_settle_time = 10; opponent = 10; drive_timeout = 600; wait(10, vex::timeUnits::msec); // Setting stuff
      drive_with_arm(-7, false); // Drive to stake, lift arm
      side_stakes.spin(fwd, -12, volt); wait(.2, seconds); side_stakes.setStopping(coast); pneumaticC.set(true); drive_timeout = 300; // Score preload, lift intake
      drive(4, true); side_stakes.stop(); drive_timeout = 900; // Drive away from stake
      turn_settle_time = 70; turn(-155, true); turn_settle_time = 10; // Turn to stake
      drive(-25, true); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.8, true);
      turn(-44, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20, false); pneumaticE.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticE.set(false); // Back out, drop intake, raise arm
      left_swing(48, true); // Swing into ring
      turn(52, true); // Turn to 4
      drive(7.5, true);   // Drive to 4
      swing_max_voltage = 12; cust_left_swing(90, true, .25); // Swing into 4
      turn(90, true); // Align
      drive_timeout = 400; drive_max_voltage = 10; drive(4, true); // D1 4
      drive(7, true); drive_max_voltage = 3; drive(10, true); drive_timeout = 1500; drive_max_voltage = 12; // D2 4
      cust_left_swing(57, true, .4); flex_wheel.spin(fwd, 12, volt); // Swing out of 4, reverse intake
      turn_timeout = 500; turn(115,  false); // Turn to final ring
      drive(10, true); // Approach final ring
      drive(7, true); // Pick up final ring
      turn(95.5, true); // Turn to ladder
      hook_chain.setStopping(coast); drive_kd = 9; drive_chain_cutout(-40, .5, true); // Drive into ladder
      break;

    case 2:
    // Blue ring no stake
      drive_kd = 0; drive_kp = 1; drive_settle_time = 5; drive(-2.2, false); drive_settle_time = 10; drive_kd = 4; drive_kp = .7; opponent = 10;                   
      turn(-43.5, false); // Turn to raised ring  
      pneumaticC.set(true);
      flex_wheel.spin(fwd, -12, volt);
      drive_max_voltage = 3; drive_timeout = 1000; nazi_drive(13, false); drive_max_voltage = 12; pneumaticC.set(false); // Pick up raised ring, drop intake
      drive_timeout = 1500; nazi_turn(-137, false); // Turn to stake
      nazi_drive(-22, false); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.5, true); // Align with centre
      turn(-41, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.7, false); pneumaticE.set(true); wait(.3, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticE.set(false); // Back out, drop intake, raise arm
      left_swing(48, true); // Swing into ring
      turn(52, true); // Turn to 4
      drive(5.5, true);   // Drive to 4
      swing_max_voltage = 12; cust_left_swing(90, true, .25); // Swing into 4
      turn(90, true); // Align
      drive_timeout = 400; drive_max_voltage = 10; drive(4, true); // D1 4
      drive(7, true); drive_max_voltage = 3; drive(12, true); drive_timeout = 1500; drive_max_voltage = 12; // D2 4
      cust_left_swing(57, true, .4); flex_wheel.spin(fwd, 12, volt); // Swing out of 4, reverse intake
      turn_timeout = 500; turn(115,  false); // Turn to final ring
      drive(10, true); // Approach final ring
      drive(10, true); // Pick up final ring
      turn(95.5, true); // Turn to ladder
      hook_chain.setStopping(coast); drive_kd = 9; drive_chain_cutout(-40, .5, true); // Drive into ladder
      break;
    
    case 4:
    // Blue ring no anything
      inertial_main.setHeading(180, degrees); opponent = 10;      
      drive(-20, false);
      drive_with_clamp(-16.5, false, .4); // Drive into and clamp stake
      drive(10, true);
      turn(-44, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(25.5, false); pneumaticE.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticE.set(false); // Back out, drop intake, raise arm
      left_swing(48, true); // Swing into ring
      turn(52, true); // Turn to 4
      drive(8.8, true);   // Drive to 4
      swing_max_voltage = 12; cust_left_swing(90, true, .25); // Swing into 4
      turn(90, true); // Align
      drive_timeout = 400; drive_max_voltage = 10; drive(4, true); // D1 4
      drive(7, true); drive_max_voltage = 3; drive(11, true); drive_timeout = 1500; drive_max_voltage = 12; // D2 4
      cust_left_swing(57, true, .4); flex_wheel.spin(fwd, 12, volt); // Swing out of 4, reverse intake
      turn_timeout = 500; turn(115,  false); // Turn to final ring
      drive(10, true); // Approach final ring
      drive(7, true); // Pick up final ring
      turn(95.5, true); // Turn to ladder
      hook_chain.setStopping(coast); drive_kd = 9; drive_chain_cutout(-40, .5, true); // Drive into ladder
      break;
     
    case 1:
     // Red ring
      turn_settle_time = 10; opponent = 200; drive_timeout = 600; wait(10, vex::timeUnits::msec); // Setting stuff
      drive_with_arm(-7, false); // Drive to stake, lift arm
      side_stakes.spin(fwd, -12, volt); wait(.2, seconds); side_stakes.setStopping(coast); pneumaticC.set(true); drive_timeout = 300; // Score preload, lift intake
      drive(4, true); side_stakes.stop(); drive_timeout = 900; // Drive away from stake
      turn(43.5, true); // Turn to raised ring
      drive_max_voltage = 3; nazi_drive(12, true); drive_max_voltage = 12; pneumaticC.set(false); // Pick up raised ring, drop intake
      drive_timeout = 1500; nazi_turn(137, true); // Turn to stake
      nazi_drive(-22, true); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.5, true); // Align with centre
      turn(41, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.5, false); pneumaticH.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticH.set(false); // Back out, drop intake, raise arm
      right_swing(-48, true); // Swing into ring
      turn(-52, true); // Turn to 4
      drive(5.5, true);   // Drive to 4
      swing_max_voltage = 12; cust_right_swing(-90, true, .25); // Swing into 4
      turn(-90, true); // Align
      drive_timeout = 400; drive_max_voltage = 10; drive(4, true); // D1 4
      drive(7, true); drive_max_voltage = 4; drive(7, true); drive_timeout = 1500; drive_max_voltage = 12; // D2 4
      cust_right_swing(-57, true, .4); flex_wheel.spin(fwd, 12, volt); // Swing out of 4, reverse intake
      turn_timeout = 500; turn(-115,  false); // Turn to final ring
      drive(13, true); // Approach final ring
      drive(7, true); // Pick up final ring
      turn(-95.5, true); // Turn to ladder
      hook_chain.setStopping(coast); drive_kd = 9; drive_chain_cutout(-40, .5, true); // Drive into ladder
      break;

    case 7:
    // Red ring with no ring
      turn_settle_time = 10; opponent = 200; drive_timeout = 600; wait(10, vex::timeUnits::msec); // Setting stuff
      drive_with_arm(-7, false); // Drive to stake, lift arm
      side_stakes.spin(fwd, -12, volt); wait(.2, seconds); side_stakes.setStopping(coast); pneumaticC.set(true); drive_timeout = 300; // Score preload, lift intake
      drive(4, true); side_stakes.stop(); drive_timeout = 900; // Drive away from stake
      turn_settle_time = 70; turn(155, true); turn_settle_time = 10; // Turn to stake
      drive(-25, true); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.8, true);
      turn(44, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20, false); pneumaticH.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticH.set(false); // Back out, drop intake, raise arm
      right_swing(-48, true); // Swing into ring
      turn(-52, true); // Turn to 4
      drive(7.5, true);   // Drive to 4
      swing_max_voltage = 12; cust_right_swing(-90, true, .25); // Swing into 4
      turn(-90, true); // Align
      drive_timeout = 400; drive_max_voltage = 10; drive(4, true); // D1 4
      drive(7, true); drive_max_voltage = 3; drive(10, true); drive_timeout = 1500; drive_max_voltage = 12; // D2 4
      cust_right_swing(-57, true, .4); flex_wheel.spin(fwd, 12, volt); // Swing out of 4, reverse intake
      turn_timeout = 500; turn(-115,  false); // Turn to final ring
      drive(10, true); // Approach final ring
      drive(7, true); // Pick up final ring
      turn(-95.5, true); // Turn to ladder
      hook_chain.setStopping(coast); drive_kd = 9; drive_chain_cutout(-40, .5, true); // Drive into ladder
      break;

    case 6:
    // Red ring with no stake
      drive_kd = 0; drive_kp = 1; drive_settle_time = 5; drive(-2.2, false); drive_settle_time = 10; drive_kd = 4; drive_kp = .7; opponent = 200;            
      turn(43.5, false); // Turn to raised ring  
      pneumaticC.set(true);
      flex_wheel.spin(fwd, -12, volt);
      drive_max_voltage = 3; drive_timeout = 1000; nazi_drive(13, false); drive_max_voltage = 12; pneumaticC.set(false); // Pick up raised ring, drop intake
      drive_timeout = 1500; nazi_turn(137, false); // Turn to stake
      nazi_drive(-22, false); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.5, true); // Align with centre
      turn(41, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.6, false); pneumaticH.set(true); wait(.3, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticH.set(false); // Back out, drop intake, raise arm
      right_swing(-48, true); // Swing into ring
      turn(-52, true); // Turn to 4
      drive(5.5, true);   // Drive to 4
      swing_max_voltage = 12; cust_right_swing(-90, true, .25); // Swing into 4
      turn(-90, true); // Align
      drive_timeout = 400; drive_max_voltage = 10; drive(4, true); // D1 4
      drive(7, true); drive_max_voltage = 3; drive(12, true); drive_timeout = 1500; drive_max_voltage = 12; // D2 4
      cust_right_swing(-57, true, .4); flex_wheel.spin(fwd, 12, volt); // Swing out of 4, reverse intake
      turn_timeout = 500; turn(-115,  false); // Turn to final ring
      drive(10, true); // Approach final ring
      drive(10, true); // Pick up final ring
      turn(-95.5, true); // Turn to ladder
      hook_chain.setStopping(coast); drive_kd = 9; drive_chain_cutout(-40, .5, true); // Drive into ladder
      break;

    case 8:
    // Red ring no anything
      inertial_main.setHeading(180, degrees); opponent = 200;      
      drive(-20, false);
      drive_with_clamp(-16.5, false, .4); // Drive into and clamp stake
      drive(10, true);
      turn(44, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(26, false); pneumaticH.set(true); wait(.3, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticH.set(false); // Back out, drop intake, raise arm
      right_swing(-48, true); // Swing into ring
      turn(-52, true); // Turn to 4
      drive(8.8, true);   // Drive to 4
      swing_max_voltage = 12; cust_right_swing(-90, true, .25); // Swing into 4
      turn(-90, true); // Align
      drive_timeout = 400; drive_max_voltage = 10; drive(4, true); // D1 4
      drive(7, true); drive_max_voltage = 3; drive(11, true); drive_timeout = 1500; drive_max_voltage = 12; // D2 4
      cust_right_swing(-57, true, .4); flex_wheel.spin(fwd, 12, volt); // Swing out of 4, reverse intake
      turn_timeout = 500; turn(-115,  false); // Turn to final ring
      drive(10, true); // Approach final ring
      drive(7, true); // Pick up final ring
      turn(-95.5, true); // Turn to ladder
      hook_chain.setStopping(coast); drive_kd = 9; drive_chain_cutout(-40, .5, true); // Drive into ladder
      break;
    
    case 9:
    // Red Stake
      turn_settle_time = 10; opponent = 200; drive_timeout = 600; wait(10, vex::timeUnits::msec); // Setting stuff
      drive_with_arm(-7, false); // Drive to stake, lift arm
      side_stakes.spin(fwd, -12, volt); wait(.2, seconds); side_stakes.setStopping(coast); pneumaticC.set(true); drive_timeout = 300; // Score preload, lift intake
      drive(4, true); side_stakes.stop(); drive_timeout = 900; // Drive away from stake
      turn(-43.5, true); // Turn to raised ring
      drive_max_voltage = 3; nazi_drive(12, true); drive_max_voltage = 12; pneumaticC.set(false); // Pick up raised ring, drop intake
      drive_timeout = 1500; nazi_turn(-137, true); // Turn to stake
      nazi_drive(-22, true); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.5, true); // Align with centre
      turn(-41, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.5, false); pneumaticE.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticE.set(false); // Back out, drop intake, raise arm
      left_swing(0, true); // Swing into ring
      turn(95, true); // Face bottom ring
      drive(27, true); // Drive into bottom ring
      turn(180, true);
      drive(34, true);
      turn(105, true);
      pneumaticA.set(true);
      pneumaticE.set(true);
      texecute_wait(.2);
      drive(5, true);
      turn(-24, true);
      pneumaticE.set(false);
      drive(50, true);
      drive_max_voltage = 6;
      drive(20, true);
      break;

    case 11:
    // Red stake with no ring
      turn_settle_time = 10; opponent = 200; drive_timeout = 600; wait(10, vex::timeUnits::msec); // Setting stuff
      drive_with_arm(-7, false); // Drive to stake, lift arm
      
      side_stakes.spin(fwd, -12, volt); wait(.2, seconds); side_stakes.setStopping(coast); pneumaticC.set(true); drive_timeout = 300; // Score preload, lift intake
      drive(4, true); side_stakes.stop(); drive_timeout = 900; // Drive away from stake
      turn_settle_time = 70; turn(-155, true); turn_settle_time = 10; // Turn to stake
      drive(-25, true); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.8, true);
      turn(-43.5, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.4, false); pneumaticE.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticE.set(false); // Back out, drop intake, raise arm
      left_swing(0, true); // Swing into ring
      turn(95, true); // Face bottom ring
      drive(27, true); // Drive into bottom ring
      turn(180, true);
      drive(34, true);
      turn(112, true);
      pneumaticA.set(true);
      pneumaticE.set(true);
      texecute_wait(.2);
      drive(5, true);
      turn(-24, true);
      pneumaticE.set(false);
      drive(40, true);

      turn(-140, true);

      // drive_max_voltage = 6;
      // drive(20, true);
      break;

    case 10:
    // Red stake with no stake
      drive_kd = 0; drive_kp = 1; drive_settle_time = 5; drive(-2.2, false); drive_settle_time = 10; drive_kd = 4; drive_kp = .7; opponent = 200;                   
      turn(-43.5, false); // Turn to raised ring  
      pneumaticC.set(true);
      flex_wheel.spin(fwd, -12, volt);
      drive_max_voltage = 3; drive_timeout = 1000; nazi_drive(13, false); drive_max_voltage = 12; pneumaticC.set(false); // Pick up raised ring, drop intake
      drive_timeout = 1500; nazi_turn(-137, false); // Turn to stake
      nazi_drive(-22, false); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.5, true); // Align with centre
      turn(-41, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.5, false); pneumaticE.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticE.set(false); // Back out, drop intake, raise arm
      left_swing(0, true); // Swing into ring
      turn(95, true); // Face bottom ring
      drive(27, true); // Drive into bottom ring
      turn(180, true);
      drive(34, true);
      turn(110, true);
      pneumaticA.set(true);
      pneumaticE.set(true);
      texecute_wait(.2);
      drive(5, true);
      turn_settle_time = 50; 
      turn(-26, true);
      pneumaticE.set(false);
      drive(40, true);

      turn(-140, true);
      break;

    case 12:
    // Red stake with no anything
      inertial_main.setHeading(180, degrees); opponent = 200;      
      drive(-20, false);
      drive_with_clamp(-16.5, false, .4); // Drive into and clamp stake
      drive(10, true);
      turn(-42.5, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(26, false); pneumaticE.set(true); wait(.3, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticE.set(false); wait(.3, seconds); // Back out, drop intake, raise arm
      left_swing(0, true); // Swing into ring
      turn(95, true); // Face bottom ring
      drive(27, true); // Drive into bottom ring
      turn(180, true);
      drive(34, true);
      turn(110, true);
      pneumaticA.set(true);
      pneumaticE.set(true);
      texecute_wait(.2);
      drive(5, true);
      turn_settle_time = 50; 
      turn(-26, true);
      pneumaticE.set(false);
      drive(40, true);

      turn(-140, true);

      // drive_max_voltage = 6;
      // drive(20, true);
      break;

    case 13:
    // Blue stake
      turn_settle_time = 10; opponent = 10; drive_timeout = 600; wait(10, vex::timeUnits::msec); // Setting stuff
      drive_with_arm(-7, false); // Drive to stake, lift arm
      side_stakes.spin(fwd, -12, volt); wait(.2, seconds); side_stakes.setStopping(coast); pneumaticC.set(true); drive_timeout = 300; // Score preload, lift intake
      drive(4, true); side_stakes.stop(); drive_timeout = 900; // Drive away from stake
      turn(43.5, true); // Turn to raised ring
      drive_max_voltage = 3; nazi_drive(12, true); drive_max_voltage = 12; pneumaticC.set(false); // Pick up raised ring, drop intake
      drive_timeout = 1500; nazi_turn(137, true); // Turn to stake
      nazi_drive(-22, true); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.5, true); // Align with centre
      turn(41, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.5, false); pneumaticH.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticH.set(false); // Back out, drop intake, raise arm
      right_swing(0, true); // Swing into ring
      turn(-95, true); // Face bottom ring
      drive(27, true); // Drive into bottom ring
      turn(180, true);
      drive(34, true);
      turn(-105, true);
      pneumaticA.set(true);
      pneumaticH.set(true);
      texecute_wait(.2);
      drive(5, true);
      turn(24, true);
      pneumaticH.set(false);
      drive(50, true);
      drive_max_voltage = 6;
      drive(20, true);
      break;

    case 15:
    // Blue ring stake no ring
      turn_settle_time = 10; opponent = 10; drive_timeout = 600; wait(10, vex::timeUnits::msec); // Setting stuff
      drive_with_arm(-7, false); // Drive to stake, lift arm
      side_stakes.spin(fwd, -12, volt); wait(.2, seconds); side_stakes.setStopping(coast); pneumaticC.set(true); drive_timeout = 300; // Score preload, lift intake
      drive(4, true); side_stakes.stop(); drive_timeout = 900; // Drive away from stake
      turn_settle_time = 70; turn(155, true); turn_settle_time = 10; // Turn to stake
      drive(-25, true); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.8, true);
      turn(44, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20, false); pneumaticH.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticH.set(false); // Back out, drop intake, raise arm
      right_swing(0, true); // Swing into ring
      turn(-95, true); // Face bottom ring
      drive(27, true); // Drive into bottom ring
      turn(180, true);
      drive(34, true);
      turn(-105, true);
      pneumaticA.set(true);
      pneumaticH.set(true);
      texecute_wait(.2);
      drive(5, true);
      turn(24, true);
      pneumaticH.set(false);
      drive(50, true);
      drive_max_voltage = 6;
      drive(20, true);
      break;

    case 14:
    // Blue stake no stake
      drive_kd = 0; drive_kp = 1; drive_settle_time = 5; drive(-2.2, false); drive_settle_time = 10; drive_kd = 4; drive_kp = .7; opponent = 10;                   
      turn(43.5, false); // Turn to raised ring  
      pneumaticC.set(true);
      flex_wheel.spin(fwd, -12, volt);
      drive_max_voltage = 3; drive_timeout = 1000; nazi_drive(13, false); drive_max_voltage = 12; pneumaticC.set(false); // Pick up raised ring, drop intake
      drive_timeout = 1500; nazi_turn(137, false); // Turn to stake
      nazi_drive(-22, false); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.5, true); // Align with centre
      turn(41, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.5, false); pneumaticH.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticH.set(false); // Back out, drop intake, raise arm
      right_swing(0, true); // Swing into ring
      turn(-95, true); // Face bottom ring
      drive(27, true); // Drive into bottom ring
      turn(180, true);
      drive(34, true);
      turn(-105, true);
      pneumaticA.set(true);
      pneumaticH.set(true);
      texecute_wait(.2);
      drive(5, true);
      turn(24, true);
      pneumaticH.set(false);
      drive(50, true);
      drive_max_voltage = 6;
      drive(20, true);
      break;

    case 16:
    // Blue stake no anything
      inertial_main.setHeading(180, degrees); opponent = 10;      
      drive(-20, false);
      drive_with_clamp(-16.5, false, .4); // Drive into and clamp stake
      drive(10, true);
      turn(44, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(26.3, false); pneumaticH.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticH.set(false); // Back out, drop intake, raise arm
      right_swing(0, true); // Swing into ring
      turn(-95, true); // Face bottom ring
      drive(27, true); // Drive into bottom ring
      turn(180, true);
      drive_timeout = 1500;
      drive(38, true);
      turn(-110, true);
      pneumaticA.set(true);
      pneumaticH.set(true);
      texecute_wait(.5);
      drive(6, true);
      turn(24, true);
      pneumaticH.set(false);      
      drive(40, true);
      turn(140, true);
      // drive_max_voltage = 6;
      // drive(20, true);
      break;

    case 17:
    // Blue ring PLAYOFF
      turn_settle_time = 10; opponent = 10; drive_timeout = 600; wait(10, vex::timeUnits::msec); // Setting stuff
      drive_with_arm(-7, false); // Drive to stake, lift arm
      side_stakes.spin(fwd, -12, volt); wait(.2, seconds); side_stakes.setStopping(coast); pneumaticC.set(true); drive_timeout = 300; // Score preload, lift intake
      drive(4, true); side_stakes.stop(); drive_timeout = 900; // Drive away from stake
      turn(-43.5, true); // Turn to raised ring
      drive_max_voltage = 3; nazi_drive(12, true); drive_max_voltage = 12; pneumaticC.set(false); // Pick up raised ring, drop intake
      drive_timeout = 1500; nazi_turn(-137, true); // Turn to stake
      nazi_drive(-22, true); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.5, true); // Align with centre
      turn(-41, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.5, false); pneumaticE.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticE.set(false); // Back out, drop intake, raise arm
      left_swing(48, true); // Swing into ring
      turn(52, true); // Turn to 4
      drive(5.5, true);   // Drive to 4
      swing_max_voltage = 12; cust_left_swing(90, true, .25); // Swing into 4
      turn(90, true); // Align
      drive_timeout = 400; drive_max_voltage = 10; drive(4, true); // D1 4
      drive(7, true); drive_max_voltage = 4; drive(7, true); drive_timeout = 1500; drive_max_voltage = 12; // D2 4
      cust_left_swing(57, true, .4); flex_wheel.spin(fwd, 12, volt); // Swing out of 4, reverse intake
      turn_timeout = 500; turn(115,  false); // Turn to final ring
      drive(13, true); // Approach final ring
      drive(7, true); // Pick up final ring
      turn(70, true); // Turn to ladder
      drive_kp = 2; drive(-200, true);
      break;

    case 18:
     // Red ring PLAYOFF
      turn_settle_time = 10; opponent = 200; drive_timeout = 600; wait(10, vex::timeUnits::msec); // Setting stuff
      drive_with_arm(-7, false); // Drive to stake, lift arm
      side_stakes.spin(fwd, -12, volt); wait(.2, seconds); side_stakes.setStopping(coast); pneumaticC.set(true); drive_timeout = 300; // Score preload, lift intake
      drive(4, true); side_stakes.stop(); drive_timeout = 900; // Drive away from stake
      turn(43.5, true); // Turn to raised ring
      drive_max_voltage = 3; nazi_drive(12, true); drive_max_voltage = 12; pneumaticC.set(false); // Pick up raised ring, drop intake
      drive_timeout = 1500; nazi_turn(137, true); // Turn to stake
      nazi_drive(-22, true); // Approach stake
      drive_with_clamp(-16, false, .4); // Drive into and clamp stake
      drive(5.5, true); // Align with centre
      turn(41, true); pneumaticC.set(true); hook_chain.stop(); // Turn to centre, lift intake, stop hook chain
      wait(200, vex::timeUnits::msec); drive(20.5, false); pneumaticH.set(true); wait(.1, seconds); // Drive to centre, lower arm
      drive(-24, false); pneumaticC.set(false); pneumaticH.set(false); // Back out, drop intake, raise arm
      right_swing(-48, true); // Swing into ring
      turn(-52, true); // Turn to 4
      drive(5.5, true);   // Drive to 4
      swing_max_voltage = 12; cust_right_swing(-90, true, .25); // Swing into 4
      turn(-90, true); // Align
      drive_timeout = 400; drive_max_voltage = 10; drive(4, true); // D1 4
      drive(7, true); drive_max_voltage = 4; drive(7, true); drive_timeout = 1500; drive_max_voltage = 12; // D2 4
      cust_right_swing(-57, true, .4); flex_wheel.spin(fwd, 12, volt); // Swing out of 4, reverse intake
      turn_timeout = 500; turn(-115,  false); // Turn to final ring
      drive(13, true); // Approach final ring
      drive(7, true); // Pick up final ring
      turn(-70, true); // Turn to ladder
      drive_kp = 2; drive(-200, true);
      break;

      

  }

}        

void l2_reserve(){
  if (Controller1.ButtonL2.pressing()) {
    hook_chain.spin(forward);
    hook_chain.setVelocity(20, percent);
  }
}

/*---------------------------------------------------------------------------*/                 
/*                                                                           */                 
/*                              User Control Task                            */                 
/*                                                                           */               
/*  This task is used to control your robot during the user control phase of */                 
/*  a VEX Competition.                                                        */                 
/*                                                                           */                 
/*  You must modify the code to add your own robot specific commands here.   */                 
/*---------------------------------------------------------------------------*/                 
 void usercontrol(void) {                 

  pneumaticA.set(true);  
  side_stakes.setStopping(hold);
  scoring_system.setStopping(hold);
  bool bpneumaticA = true;
  bool bpneumaticH = false;
  bool bpneumaticG = false;
  bool bpneumaticF = true;
  bool bpneumaticE = true;
  bool spin_to_location = false;
  pneumaticG.set(false);
  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;                              
  float arminput = 0;                 
  base_max_voltage = arm_max_voltage;                 
  base_kd = arm_kd;                 
  base_ki = arm_ki;                 
  base_kp = arm_kp;                 
  base_starti = arm_starti;                 
  base_settle_error = arm_settle_error;                 
  base_settle_time = arm_settle_time;                 
  base_timeout = arm_timeout;  
  side_stakes.spin(forward);
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;
  bool opt = false;

  while (1) {           


    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(2, 2);
    Brain.Screen.print(op.hue());

    if (100 < arm.angle(degrees)  && arm.angle(degrees) < 355) {
      side_stakes.setStopping(hold);
    }
    else {
      side_stakes.setStopping(coast);
    }

    float leftthrottle = deadband(controller(primary).Axis3.value(), 5);
    float rightthrottle = deadband(controller(primary).Axis2.value(), 5);

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


    if (Controller1.ButtonX.pressing() && !opt) {
      opt = true;
      wait(.2, seconds);
    }
    else if (Controller1.ButtonX.pressing()) {
      opt = false;
      wait(.2, seconds);
    }

    if (Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing()){
      spin_to_location = true;
    }
    if (arm.angle() > 336 and arm.angle() < 341){
      spin_to_location = false;
    }

    if (!spin_to_location){
      if (Controller1.ButtonLeft.pressing()){
        if (arm.angle() < 336){
          side_stakes.spin(fwd, -3, volt);
        }
        else if (arm.angle() > 343){
          side_stakes.spin(fwd, 3, volt);
        }
        else {
          side_stakes.stop();
        }
      }

      else {
        if (Controller1.ButtonL2.pressing()) {
          side_stakes.spin(fwd, 12, volt);
        }
        else if (Controller1.ButtonL1.pressing()) {
          side_stakes.spin(fwd, -12, volt);
        }
        else{
          side_stakes.stop();
        }
      }
    }
    else {
      if (arm.angle() < 300 && arm.angle() > 100){
        side_stakes.spin(fwd, -5, volt);
      }
      else if (arm.angle() < 335 && arm.angle() > 100){
        side_stakes.spin(fwd, -2, volt);
      }
      else if (arm.angle() > 343 or arm.angle() < 100){
        side_stakes.spin(fwd, 3, volt);
      }
      else {
        side_stakes.stop();
      }
    }

    op.setLight(ledState::on);
    op.setLightPower(100, percent);

    if (opt) {
      if (opponent == 200){
        if (Controller1.ButtonR2.pressing() && b <= .04) { 
          scoring_system.spin(fwd, -12, volt);
        }
        else if (Controller1.ButtonR1.pressing()) {
          scoring_system.spin(fwd, 12, volt);
        }
        else if (Controller1.ButtonR2.pressing()){    
          flex_wheel.spin(fwd, -12, volt);  hook_chain.stop();
        }
        else {
          scoring_system.stop();  l2_reserve();
        }
      }
      else{
        if (Controller1.ButtonR2.pressing() && r <= .04) { 
          scoring_system.spin(fwd, -12, volt);
        }
        else if (Controller1.ButtonR1.pressing()) {
          scoring_system.spin(fwd, 12, volt);
        }
        else if (Controller1.ButtonR2.pressing()){    
          flex_wheel.spin(fwd, -12, volt);  hook_chain.stop();
        }
        else {
          scoring_system.stop();  l2_reserve();
        }
      }
    }

    else {

      if(Controller1.ButtonR2.pressing()) {

        scoring_system.spin(fwd, -12, volt);

      }

      else if (Controller1.ButtonR1.pressing()) {

        scoring_system.spin(fwd, 12, volt);

      }

      else if (Controller1.ButtonR2.pressing()){
        
        flex_wheel.spin(fwd, -12, volt);
        hook_chain.stop();

      }

      else {

        scoring_system.stop();
        l2_reserve();

      }

    }

    if (op.hue() <= 10) {

      boolrd = true;

    }

    if (op.hue() > 200) {

      boolbd = true;

    }

    if (boolrd) {
      if (d1.objectDistance(inches) < 3){
        boolr = true;
      }
    }

    if (boolbd) {
      if (d1.objectDistance(inches) < 3){
        boolb = true;
      }
    }
   
    if (b >= .8) {
      b = 0;
      boolb = false;

    }

    if (r >= .8) {
      r = 0;
      boolr = false;
    }

    if (boolr == true){
      r += .02;
    }

    if (boolb == true){
      b += .02;
    }

    if (r >= .2 or b >= .2){
      boolbd = false; boolrd = false; b = 0; r = 0; boolr = false; boolb = false;
    }


    if (Controller1.ButtonDown.pressing() && !bpneumaticA) {
      bpneumaticA = true;
      wait(.2, seconds);
    }
    else if (Controller1.ButtonDown.pressing()){
      bpneumaticA = false;
      wait(.2, seconds);
    }

    if (bpneumaticA) {
      pneumaticA.set(false);
    }
    else {
      pneumaticA.set(true);
    }    

    if (Controller1.ButtonY.pressing() && !bpneumaticE) {
      bpneumaticE = true;
      wait(.2, seconds);
    }
    else if (Controller1.ButtonY.pressing()){
      bpneumaticE = false;
      wait(.2, seconds);
    }

    if (bpneumaticE) {
      pneumaticE.set(false);
    }
    else {
      pneumaticE.set(true);
    }    

    if (Controller1.ButtonB.pressing() && !bpneumaticF) {
      bpneumaticF = true;
      wait(.2, seconds);
    }
    else if (Controller1.ButtonB.pressing()){
      bpneumaticF = false;
      wait(.2, seconds);
    }

    if (bpneumaticF) {
      pneumaticF.set(false);
    }
    else {
      pneumaticF.set(true);
    }          

    if (Controller1.ButtonRight.pressing() && bpneumaticH) {
      bpneumaticH = false;
      wait(.2, seconds);
    }
    else if (Controller1.ButtonRight.pressing()){
      bpneumaticH = true;
      wait(.2, seconds);
    }

    if (bpneumaticH) {
      pneumaticH.set(true);
    }
    else {
      pneumaticH.set(false);
    } 

    if (Controller1.ButtonUp.pressing() && bpneumaticG) {
      bpneumaticG = false;
      wait(.2, seconds);
    }
    else if (Controller1.ButtonUp.pressing()){
      bpneumaticG = true;
      wait(.2, seconds);
    }

    if (bpneumaticG) {
      pneumaticC.set(true);
    }
    else {
      pneumaticC.set(false);
    } 

                 
    wait(20, msec); // Sleep the task for a short amount of time to                 
                    // prevent wasted resources.                 
  }                 
}                 
                 
//                 
// Main will set up the competition functions and callbacks.                 
//                 
int main() {                 
  // Set up callbacks for autonomous and driver control periods.                 
  Competition.autonomous(autonomous);                 
  Competition.drivercontrol(usercontrol);                 
                 
  // Run the pre-autonomous function.                 
  pre_auton();                 
                 
  // Prevent main from exiting with an infinite loop.                 
  while (true) {                 
    wait(100, msec);                 
  }                 
}             