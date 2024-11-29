#include "main.h"

void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	pros::Controller controller (pros::E_CONTROLLER_MASTER);

	pros::MotorGroup left_mg({1, 2}, pros::MotorGear::blue);
	pros::MotorGroup right_mg({-3, -4}, pros::MotorGear::blue);

	lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              	  &right_mg, // right motor group
                                  10, // 10 inch track width
                                  lemlib::Omniwheel::NEW_4, // using new 4" omnis
                                  360, // drivetrain rpm is 360
                                  2 // horizontal drift is 2 (for now)
	);

	while (true) {

		// Simple controls
		int dir = controller.get_analog(ANALOG_LEFT_Y);
		int turn = controller.get_analog(ANALOG_RIGHT_X);
		left_mg.move(dir - turn);
		right_mg.move(dir + turn);

		// Delay to not flood the CPU.
		pros::delay(20);
	}
}