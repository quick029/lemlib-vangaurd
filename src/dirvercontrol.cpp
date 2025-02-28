#include "drivercontrol.h" // IWYU pragma: keep
#include "main.h"

void buttonControlls() {
  // intake
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && intake.get_direction() != 1) {
    intake.move(127);
    while (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      pros::delay(10);
    }
  }
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && intake.get_direction() == 1) {
    intake.brake();
    while (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        pros::delay(10);
      }
  }
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && intake.get_direction() != -1) {
    intake.move(-127);
    while (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      pros::delay(10);
    }
  }
}