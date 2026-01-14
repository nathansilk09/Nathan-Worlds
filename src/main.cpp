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

  intake.spin(fwd);

  while (1) {           


    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(2, 2);
    
    drive();
    intakemove();
    activateoutake();
    pnuematicsgo();
    
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