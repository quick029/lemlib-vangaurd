#include "drivercontrol.h" // IWYU pragma: keep
#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

bool isClamped = false;
bool isIntaking = false;
bool intakeReversed = false;
bool wallStakeActive = false;

void buttonControls(void *param) {
  rot.reset_position();
  while (true) {
    // clamp
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && isClamped) {
      clamp.set_value(false);
      clamp2.set_value(false);
      isClamped = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) &&
               !isClamped) {
      clamp.set_value(true);
      clamp2.set_value(true);
      isClamped = true;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        pros::delay(50);
      }
    }

    // intake
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) &&
        (!isIntaking || intakeReversed)) {
      intake.move(-127);
      isIntaking = true;
      intakeReversed = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) &&
               isIntaking && !intakeReversed) {
      intake.brake();
      isIntaking = false;
      intakeReversed = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) &&
               (!isIntaking || !intakeReversed)) {
      intake.move(127);
      isIntaking = true;
      intakeReversed = true;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        pros::delay(50);
      }
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) &&
               isIntaking && intakeReversed) {
      intake.brake();
      isIntaking = false;
      intakeReversed = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        pros::delay(50);
      }
    }

    // wall stake
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) &&
        !wallStakeActive) {
      lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
      lift.move_relative(40, 50);
      wallStakeActive = true;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        pros::delay(50);
      }
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
      lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
      lift.brake();
      wallStakeActive = false;
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        pros::delay(50);
      }
    }
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) &&
        wallStakeActive && rot.get_position()/100 < 250) {
      lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      lift.move_relative(260, 127);
      while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        pros::delay(50);
      }
    }
  }
}