#include "auton.h"
#include "drivercontrol.h"
#include "lemlib-tarball/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cmath>

auton_type autonType = SKILLS;
bool scoreAllianceStake = true;
bool autonConfirmed = true;

ASSET(skills_path_txt);

lemlib_tarball::Decoder decoder(skills_path_txt);

void clampSet(bool value) {
  clamp.set_value(value);
  clamp2.set_value(value);
}

enum wallStakePos { PASSIVE, ACTIVE, SCORING };

void setWallStakePos(wallStakePos pos) {
  if (pos == PASSIVE) {
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    lift.brake();
  } else if (pos == ACTIVE) {
    wallStakeEnc.reset_position();
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(20);
    while (wallStakeEnc.get_position() < 4500) {
      pros::delay(10);
    }
    lift.brake();
  } else if (pos == SCORING) {
    lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lift.move_relative(310, 127);
  }
}

void runAuton() {
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
  while (!autonConfirmed) {
    pros::delay(50);
  }
  pros::delay(1500);
  if (autonType == RED_POSITIVE && scoreAllianceStake) {

    chassis.setPose(60, 17, 0);
    chassis.moveToPose(60, 0, 0, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 0, 10000, {.forwards = false, .maxSpeed = 27});
    while (distance.get_distance() > 127) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, 27, 700, {.forwards = false});
    chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(180, 200);
    
    chassis.moveToPoint(30, 47, 2300);
    chassis.turnToHeading(0, 2000);
    chassis.moveToPoint(30, 0, 2000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == RED_POSITIVE && !scoreAllianceStake) {
    
    chassis.setPose(60, 27, 90);
    chassis.turnToPoint(30, 27, 700, {.forwards = false});
    chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(180, 200);
    
    chassis.moveToPoint(30, 47, 2300);
    chassis.turnToHeading(0, 2000);
    chassis.moveToPoint(30, 0, 2000, {.maxSpeed = 80});
    chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == RED_NEGATIVE && scoreAllianceStake) {
    chassis.setPose(60, -17, 180);
    chassis.moveToPose(60, 0, 180, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 0, 10000, {.forwards = false, .maxSpeed = 27});
    while (distance.get_distance() > 127) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, -27, 700, {.forwards = false});
    chassis.moveToPoint(30, -27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true); 
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(0, 200);

    chassis.moveToPoint(30, -47, 2300);

    chassis.turnToPoint(19, -48, 500);
    chassis.moveToPoint(19, -48, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(30, -48, 1000, {.forwards = false});
    chassis.turnToPoint(19, -51, 700);
    chassis.moveToPoint(19, -51, 2000);
    // chassis.waitUntilDone();
    isClamped = true;
  }else if (autonType == RED_NEGATIVE && !scoreAllianceStake) {


  }


  else if (autonType == BLUE_POSITIVE && scoreAllianceStake) {
    chassis.setPose(60, -17, 180);
    chassis.moveToPose(60, 0, 180, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 0, 10000, {.forwards = false, .maxSpeed = 27});
    while (distance.get_distance() > 127) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, -27, 700, {.forwards = false});
    chassis.moveToPoint(30, -27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(0, 200);

    chassis.moveToPoint(30, -47, 2300);
    chassis.turnToHeading(180,2000);
    chassis.moveToPoint(30, 0, 2000, {.maxSpeed = 80});
    // chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == BLUE_POSITIVE && !scoreAllianceStake) {
    // code
  }

  else if (autonType == BLUE_NEGATIVE && scoreAllianceStake) {
    
    chassis.setPose(60, 17, 0);
    chassis.moveToPose(60, 0, 0, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 0, 10000, {.forwards = false, .maxSpeed = 27});
    while (distance.get_distance() > 127) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToPoint(30, 27, 700, {.forwards = false});
    chassis.moveToPoint(30, 27, 1250, {.forwards = false, .maxSpeed = 80});
    // chassis.moveToPose(30, -25, 70, 2250, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(180, 200);
    
    chassis.moveToPoint(30, 47, 2300);
  
    chassis.turnToPoint(19, 48, 500);
    chassis.moveToPoint(19, 48, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(30, 48, 1000, {.forwards = false});
    chassis.turnToPoint(19, 51, 700);
    chassis.moveToPoint(19, 51, 2000);
    chassis.waitUntilDone();
    isClamped = true;
  }

  else if (autonType == BLUE_NEGATIVE && !scoreAllianceStake) {
    // code
  }

  else if (autonType == SKILLS) {
    chassis.setPose(-55, 0, 90);
    intake.move(127);
    pros::delay(300);
    intake.brake();
    chassis.moveToPoint(-53, 0, 1000, {.minSpeed = 35});
    chassis.turnToHeading(270, 1000);
    chassis.follow(decoder["Mogo 1"], 7.8, 10000, false);
    chassis.waitUntilDone();
    clampSet(true);
    chassis.turnToHeading(90, 700);
    chassis.waitUntilDone();
    intake.move(127);
    chassis.follow(decoder["Ring 1"], 8.2, 10000);
    chassis.follow(decoder["Align 0"], 8.2, 10000, false);
    chassis.turnToHeading(0, 1000);
    chassis.waitUntilDone();
    setWallStakePos(ACTIVE);
    chassis.follow(decoder["Wall 1"], 8, 1000);
    chassis.waitUntilDone();
    pros::delay(2000);
    intake.brake();
    chassis.turnToHeading(0, 300);
    chassis.moveToPoint(-3, 61, 500);
    chassis.waitUntilDone();
    setWallStakePos(SCORING);
    pros::delay(1000);
    setWallStakePos(PASSIVE);
    // clampSet(true); // TEMPORARY
    chassis.setPose(-2, 52, 0);
    chassis.moveToPoint(-2, 47, 1000);
    chassis.turnToHeading(195, 1000);
    intake.move(127);
    chassis.follow(decoder["Ring 2"], 12, 10000);
    chassis.waitUntilDone();
    pros::delay(1000);
    chassis.follow(decoder["Align 1"], 12, 10000, false);
    chassis.turnToHeading(300, 700);
    chassis.follow(decoder["Ring 3"], 12, 10000);
    chassis.turnToHeading(110, 700);
    chassis.waitUntilDone();
    pros::delay(1000);
    intake.brake();
    chassis.follow(decoder["Corner 1"], 12, 10000, false);
    chassis.waitUntilDone();
    clampSet(false);
    chassis.turnToHeading(165, 700);
    chassis.follow(decoder["Align 2"], 8, 10000);
    chassis.turnToHeading(0, 700);
    chassis.follow(decoder["Mogo 2"], 8, 10000, false);
    chassis.waitUntilDone();
    clampSet(true);
    chassis.turnToHeading(90, 700);
    chassis.follow(decoder["Ring 4"], 8, 10000);
    chassis.follow(decoder["Align 3"], 8, 10000, false);
    chassis.turnToHeading(255, 700);
    chassis.follow(decoder["Ring 5"], 8, 10000, false);
    chassis.turnToHeading(80, 700);
    chassis.waitUntilDone();
    clampSet(false);
    chassis.follow(decoder["Corner 2"], 8, 10000, false);
    chassis.follow(decoder["Ring 6"], 8, 10000, false);
    chassis.turnToHeading(225, 700);
    chassis.follow(decoder["Mogo 3"], 8, 10000, false);
    chassis.waitUntilDone();
    clampSet(true);
    chassis.turnToHeading(225, 700);
    chassis.follow(decoder["Ring 7"], 8, 10000, false);    
    chassis.turnToHeading(0, 700);
    chassis.follow(decoder["Corner 3"], 8, 10000, false); 
    chassis.waitUntilDone();
    clampSet(false);
    chassis.moveToPoint(50, -66, 1000);   
  }
}