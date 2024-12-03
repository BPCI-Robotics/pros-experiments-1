#include "main.h"

ASSET(example_txt);

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


// TODO: review those
// https://github.com/LemLib/LemLib/blob/stable/src/main.cpp
// https://www.vexforum.com/t/a-pid-controller-in-robotc/20105
// https://squiggles.readthedocs.io/en/latest/maths.html
// https://wiki.purduesigbots.com/software/path-planning
// lemlib::Chassis chassis (drivetrain, );

void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {

    chassis.setPose(0, 0, 0);

    chassis.follow(example_txt, 15, 2000);
}

void opcontrol() {
	int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int leftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

        

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