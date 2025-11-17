/*----------------------------------------------------------------------------*/                 
/*                                                                            */                 
/*    Module:       main.cpp                                                  */                 
/*    Author:       Student                                                   */                 
/*    Created:      3/12/2024, 2:22:38 PM                                     */                 
/*    Description:  V5 project                                                */                 
/*                                                                            */                 
/*----------------------------------------------------------------------------*/                 
                 
#include <cmath>
#include "tank.cpp"
                 
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
                 

float to_percent(float volt){                 
  return(volt/12.0*100.0);                 
}    
              

float distance_sense_width = 9; // Width between distance sensors

// Convert distance sensor values to an angle
// float distance_angle() {
//   return(90-(atan((distance_sense_width)/(d1.objectDistance(inches) - d2.objectDistance(inches)))));
// }


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
float drive_kp = .5;                 
float drive_ki = 0;                 
float drive_kd = 2;                 
float drive_starti = 15;                 
float drive_settle_error = .5;                 
float drive_settle_time = 50;                 
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
// float trackingwheel(){                 
                
//   return((tw.angle()+(360*twm))*tw_drive_multiplier);   

// }   

// Updates left chassis position
float get_left_position_in() {                 
                 
  return(left_chassis.position(degrees)*drive_multiplier);                 
                 
}                 

// Updates right chassis position
float get_right_position_in() {                 
                 
  return(right_chassis.position(degrees)*drive_multiplier);                 
                 
}         

float get_average_position_in() {                 
                 
  return((get_left_position_in()+get_right_position_in())/2);                 
                 
}  

float get_absolute_heading() {

  return(reduce_0_to_360(inertial_main.heading(degrees)));

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

    
// Drives in a straight line a given distance
void drive(float inches) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  start_average_position = get_average_position_in();                 
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
  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
 

  // All of that is just effectively resetting values and making sure the PID values matches the drive PID values 

  // Start of the loop     
  while (!finished) {                 
    
    // Updates tracking wheel rotations
    
    
    average_position = get_average_position_in();        
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
                    
    drive_with_voltage(-(drive_output + heading_output), -(drive_output - heading_output)); // Drives with calculated voltages
    previous_error = average_position;
    vex::task::sleep(10);                 
                 
  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();                 
                 
}     



// Drives in a straight line a given distance
void drive_with_target(float inches, float angle) {                 

  accumulated_error = 0;
  time_spent_running = 0;
  finished = false;               
  start_average_position = get_average_position_in();                 
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
  right_chassis.setStopping(hold);
  left_chassis.setStopping(hold);
  b = 0;
  r = 0;
  boolb = false;
  boolr = false;  

  // All of that is just effectively resetting values and making sure the PID values matches the drive PID values 

  // Start of the loop     
  while (!finished) {                 

    average_position = get_average_position_in();        
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
                    
    drive_with_voltage(-(drive_output + heading_output), -(drive_output - heading_output)); // Drives with calculated voltages

    previous_error = average_position;
    vex::task::sleep(10);                 
                 
  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();                 
                 
}   

//turns to given heading
void turn(float tdegrees) {                 

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

    drive_with_voltage(-turn_output, turn_output); // Turns with calculated voltages
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop(); 
               
}    
 

// Swings one side to a given angle   
void right_swing(float sdegrees) {                 

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
  
    drive_with_voltage(0, -swing_output); // Left swings with calculated voltages
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();
                 
}                 
                 
// Swings one side to a given angle   
void left_swing(float sdegrees) {                 

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

    drive_with_voltage(swing_output, 0); // Left swings with calculated voltages
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();
                 
}     

// Swings one side to a given angle but the other side drives at a given mult of the other side  
void cust_left_swing(float sdegrees, float mult) {                 

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

    drive_with_voltage(swing_output, swing_output*mult); // Left swings with calculated voltages
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();
                 
}    

// Swings one side to a given angle but the other side drives at a given mult of the other side  
void cust_right_swing(float sdegrees, float mult) {                 

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

    drive_with_voltage(-swing_output*mult, -swing_output);
    vex::task::sleep(10);

  }                 
                 
  left_chassis.stop();                 
  right_chassis.stop();
                 
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

    case 1:
      drive(10);
      break;

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

  while (1) {           


    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(2, 2);
    
    drive();

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