/**
 * This project is meant to be a jump start for vrc programmers to easily get
 * started with PROS and Okapi.
 *
 * To make sure you have PROS installed on your computer: https://pros.cs.purdue.edu/v5/getting-started/index.html
 *
 * See this tutorial for a reference: https://okapilib.github.io/OkapiLib/md_docs_tutorials_walkthrough_clawbot.html
 */

#include "main.h"
#include "team/robot.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello World!");
}

void disabled() {}
void competition_initialize() {}

void tuneStraightScale() {
    // TODO: put the code for tuning the straight scale here
    // before you start, mark where the is:
    //     with a piece of tape
    //     by placing the robot against a field's wall
    //     putting the back of the robot between the seams of two tiles
    //     or whatever you come up with you get the idea
    //
    // also mark where you want the robot to go with the same methods above
    // tell the robot to move a specific distance (i.e. 48 inches or 2 tiles)
    drive->moveDistance(24_in);

    // wait to let the robot settle, and to determine whether you need to increase or decrease your straight scale variable
    pros::delay(2000);

    // tell the robot to move back the same distance you told it to move forward
    drive->moveDistance(-24_in);

    // When the robot moves forward accurately enough for your taste then you can tune the turning scales variable in the next section

}

void tuneTurnScale() {
    // TODO: put the code for tuning the turn scale here
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    std::cout << "autonomous begin\n";

    /** For testing, comment one of these method calls at a time **/
    tuneStraightScale();
    // tuneTurnScale();

    std::cout << "autonomous end\n";
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    std::cout << "driver control begin\n";

    autonomous();

    while (true) {
        // Split Arcade drive more control over robot see: https://okapilib.github.io/OkapiLib/classokapi_1_1SkidSteerModel.html#aa9b68af25f8f924117b07a5c8e9f6c93
        drive->getModel()->driveVector(master->getAnalog(ControllerAnalog::rightY),
                                       master->getAnalog(ControllerAnalog::leftX));


		pros::delay(10);
	}
}
