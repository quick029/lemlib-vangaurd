#include "auton.h"
#include "main.h"
#include "pros/rtos.hpp"

auton_type autonType = NONE;
bool scoreAllianceStake = true;
bool autonConfirmed = false;

void runAuton() {
  while (!autonConfirmed) {
    pros::delay(50);
  }
  pros::delay(1500); 
  if (autonType == RED_POSITIVE && scoreAllianceStake) {
    
    chassis.setPose(60, 17, 0);
    // recordPID();
    // pros::delay(5000);
    chassis.moveToPose(60, 0, 0, 2000,{.forwards = false, .maxSpeed = 40});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73,-3,10000,{.forwards = false, .maxSpeed = 23});
    while(distance.get_distance()>127){
        pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.moveToPose(30, 22, 110, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.moveToPose(32,45,0,2000);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.turnToPoint(20, 4, 700);
    chassis.moveToPose(20,4,200,2000);
    chassis.waitUntilDone();
    intake.brake();
    // chassis.waitUntil(10);
    // wait until the movement is done
    chassis.waitUntilDone();
  }
  
  else if (autonType == RED_POSITIVE && !scoreAllianceStake) {
    // code
  }
  
  else if (autonType == RED_NEGATIVE && scoreAllianceStake) {
    chassis.setPose(60, -17, 180);
    chassis.moveToPose(60, -0, 180, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 0, 10000, {.forwards = false, .maxSpeed = 30});
    while (distance.get_distance() > 135) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, -27, 700, {.forwards = false});
    chassis.moveToPoint(30, -27, 1150, {.forwards = false, .maxSpeed = 90});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(0, 200);

    chassis.moveToPoint(30, -47, 2300);

    chassis.turnToHeading(270, 500);
    chassis.moveToPoint(15, -48, 2000);
    chassis.waitUntilDone();

    // chassis.moveToPoint(35, -48, 1000, {.forwards = false});
    // chassis.turnToPoint(11, -59, 700);
    // chassis.moveToPoint(11, -59, 2000);
    // chassis.waitUntilDone();
  }

  else if(autonType == BLUE_POSITIVE && scoreAllianceStake) {
   
    chassis.setPose(60, -17, 180);
    chassis.moveToPose(60, -0, 180, 2000,{.forwards = false, .maxSpeed = 40});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73,3,10000,{.forwards = false, .maxSpeed = 23});
    while(distance.get_distance()>127){
        pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.moveToPose(30, -22, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.moveToPose(32,-45,0,2000);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.turnToHeading(0, 700);
    chassis.moveToPose(28,-2,0,2000);
    chassis.waitUntilDone();
    intake.brake();
    chassis.waitUntilDone();
  }

  else if(autonType == BLUE_POSITIVE && !scoreAllianceStake) {
    // code
  }

  else if(autonType == BLUE_NEGATIVE && scoreAllianceStake) {
    // code
  }

  else if(autonType == BLUE_NEGATIVE && !scoreAllianceStake) {
    // code
  }
}