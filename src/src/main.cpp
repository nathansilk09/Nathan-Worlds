/*----------------------------------------------------------------------------*/                 
/*                                                                            */                 
/*    Module:       main.cpp                                                  */                 
/*    Author:       Student                                                   */                 
/*    Created:      3/12/2024, 2:22:38 PM                                     */                 
/*    Description:  V5 project                                                */                 
/*                                                                            */                 
/*----------------------------------------------------------------------------*/                 
                 
#include <cmath>
                 
#include "vex.h"
#include "intake_outake.h"
#include "Pnuematic.h"
#include "tank.h"
#include "auton.h"

using namespace vex;      
                 
// A global instance of competition                 
competition Competition;                 
                       

void autonomous(void) {                 
  
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(2, 2);
  Brain.Screen.print("Running Auton %d", autonSelection);

  switch (autonSelection) {

    case 1: //RedWing
      drive_max_voltage = 12;
      drive(27);
      turn(-45);
      drive(10);
      PA.set(true);
      wait(.3, seconds);
      drive(-8);
      turn(-120);
      drive_timeout = 2000;
      intake.spin(fwd, 12, volt);
      drive(41.2);
      turn(180);
      PB.set(true);
      wait(.5, seconds);
      drive_timeout = 1500;
      drive(27);
      drive_kp = .9; drive_timeout = 500; drive(-4); drive(5); drive(-2); drive_timeout = 1500; drive_kp = .5;
      wait(1.2, seconds);
      drive_max_voltage = 7;
      drive_with_target(-28, 180);
      drive_max_voltage = 12;
      intake.spin(fwd, -12, volt);
      wait(.1, seconds);
      outake.spin(fwd, 12, volt);
      intake.spin(fwd, 12, volt);
      break;

      case 2: //Floor
      drive(28);
      turn(45);
      intake.spin(fwd, -12, volt);
      wait(.3, seconds);
      drive(-8);
      turn(-125);
      drive_timeout = 2000;
      intake.spin(fwd, 12, volt);
      drive(40);
      turn(180);
      PB.set(true);
      wait(.5, seconds);
      drive_timeout = 1500;
      drive(24);
      drive_kp = .9;
      drive(-2);
      drive_kp = .5;
      wait(1.2, seconds);
      drive_max_voltage = 7;
      drive_with_target(-32, 180);
      drive_max_voltage = 12;
      drive_with_target(3, 180);
      intake.spin(fwd, -12, volt);
      wait(.2, seconds);
      outake.spin(fwd, 12, volt);
      intake.spin(fwd, 12, volt);
      break;

    case 5: //Skills
      intake.spin(fwd, 12, volt);
      inertial_main.setHeading(20, degrees);
      drive(27);
      turn(45);
      drive(14);
      intake.spin(fwd, -6, volt);
      wait(.5, seconds);
      intake.stop();
      drive(-27);
      turn(90);
      intake.spin(fwd, 12, volt);
      drive(55);
      drive(-7);
      turn(135);
      drive(29);
      outake.spin(fwd, -6, volt);
      wait(.5, seconds);
      intake.stop();
      outake.stop();
      left_swing(190);
      drive(60);

    case 3: //Testing
      drive(-24);
      break;

    case 11: //Red middle experimental
      drive_timeout = 2000;
      drive_max_voltage = 10;
      heading_max_voltage = 4.2; 
      intake.spin(fwd, 12,volt);
      drive_with_target(40, 45); 
      drive_kp = .9;     
      heading_max_voltage = 3;     
      drive(-11);  
      turn(135); 
      outake.spin(fwd, 12, volt);
      drive(-18);
      intake.spin(fwd, -12, volt);
      wait(.2, seconds);
      intake.spin(fwd, 12, volt);
      outake.spin(fwd, -6, volt);
      wait(.5, seconds);
      outake.stop();
      drive(55);
      turn(180);
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

  intake.spin(fwd);

  while (1) {           


    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(2, 2);
    
    drive();
    intakemove();
    activateoutake();
    // pnuematicsgo();

    if (Controller1.ButtonUp.pressing() && !BPA) {
      BPA = true;
      wait(.3, seconds);
    }
    else if (Controller1.ButtonUp.pressing()){
      BPA = false;
      wait(.3, seconds);
    }

    if (BPA) {
      PA.set(false);
    }
    else {
      PA.set(true);
    }    

    if (Controller1.ButtonX.pressing() && !BPB) {
      BPB = true;
      wait(.3, seconds);
    }
    else if (Controller1.ButtonX.pressing()){
      BPB = false;
      wait(.3, seconds);
    }

    if (BPB) {
      PB.set(false);
    }
    else {
      PB.set(true);
    }  
    
    // Brain.Screen.print();

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