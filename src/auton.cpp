#include "auton.h"
#include "main.h"

auton_type autonType = RED_NEGATIVE;

void runAuton() {
  if (autonType == RED_NEGATIVE) {
    chassis.setPose(60, -17, 180);
    // recordPID();
    // pros::delay(5000);
    chassis.moveToPose(60, -0, 180, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(73, 3, 10000, {.forwards = false, .maxSpeed = 23});
    while (distance.get_distance() > 127) {
      pros::delay(20);
    }
    chassis.cancelMotion();
    intake.move(127);
    pros::delay(500);
    intake.brake();
    chassis.turnToHeading(60, 700);
    chassis.moveToPose(30, -20, 60, 1600, {.forwards = false});
    chassis.waitUntilDone();
    clamp.set_value(true);
    clamp2.set_value(true);
    pros::delay(200);
    intake.move(127);
    chassis.turnToHeading(0, 200);

    chassis.moveToPoint(30, -47, 2300);

    chassis.turnToHeading(270, 500);
    chassis.moveToPose(11, -43, 270, 2000);
    chassis.moveToPose(20, -43, 270, 1000, {.forwards = false});
    chassis.turnToHeading(240, 700);
    chassis.moveToPose(8, -55, 270, 2000);
    chassis.waitUntilDone();
    pros::delay(1000);
    intake.brake();
    // stopRecordingPID();
    // lv_example_chart_5();
    pros::lcd::print(4, "pure pursuit finished!");
  }
}