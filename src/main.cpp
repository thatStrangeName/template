/**
 * This project is meant to be a jump start for vrc programmers to easily get
 * started with PROS and Okapi.
 *
 * To make sure you have PROS installed on your computer: https://pros.cs.purdue.edu/v5/getting-started/index.html
 *
 * See this tutorial for a reference: https://okapilib.github.io/OkapiLib/md_docs_tutorials_walkthrough_clawbot.html
 */

#include "main.h"
#include "z839/robot.h"

pros::task_t tuneTask;

string unitType = "_in"; // This is just used for displaying units in logs

QLength getAndLogCalculatedDistance (double actualTicks, QLength wheelDiameter, double ticksPerRotation) {
    // calculate and log the calculatedDistance and ticks (ticks*diameter*1_pi)/ticksPerRotation) see: https://www.desmos.com/calculator/7dq6i84ugm
    QLength calculatedDistance = 0 * meter;
    cout << "Calculated Distance\t" << displayQLength(calculatedDistance) << unitType
         << "\tTicks\t" << actualTicks << "\n";
    return calculatedDistance;
}

QAngle getAndLogCalculatedAngle (double actualTicks, QLength wheelDiameter, double ticksPerRotation, QLength trackDiameter) {
    // calculate and log the calculatedDistance and ticks
    QLength calculatedDistance = 0 * meter;
    QAngle calculatedAngle = 0 * radian;
    cout << "Calculated Angle\t" << displayQAngle(calculatedAngle)
        << "\tTicks\t" << actualTicks << "\n";
    return calculatedAngle;
}

QLength calculateNewWheelDiameter (QLength actualDistance, QLength calculatedDistance, double actualTicks, QLength wheelDiameter, double ticksPerRotation) {
    // diameter of the left and right wheels
    cout << "Current diameter of the wheel is " << displayQLength(wheelDiameter) << unitType << "\n";

    // the ticks per rotation for each encoder is scales.tpr
    cout << "Ticks per rotation for each encoder is " << ticksPerRotation << "\n";

    /**
     * Put the code for calculating the new wheel diameter here
     * 
     * You should be able to accomplish this with the math here: https://www.desmos.com/calculator/viehxr5lqc
     * Also, use the graph linked above to determine if your program is working properly.
     */
    // Step 1. Make sure that your wheelDiameter, actualTicks, and ticksPerRotation are correct, by finding the ticks from the calculatedDistance
    double calculatedTicks = 0;

    cout << "If the calculatedTicks: " << calculatedTicks 
        << " is equal to the actualTicks: " << actualTicks 
        << ", then the following is true:" << "\n";

    // Step 2. Calculate the newWheelDiameter to set the actualTicks to a certain distance
    QLength newWheelDiameter = 0 * meter;

    cout << "If you change the wheelDiameter: " << displayQLength(wheelDiameter) << unitType 
         << " to the newWheelDiameter " << displayQLength(newWheelDiameter) << unitType
         << " then if you MOVE your robot FORWARD " << actualTicks
         << " ticks the robot should calculate that it went: " << displayQLength(actualDistance) << unitType << "\n";
    
    return newWheelDiameter;
}

QLength calculateNewTrackDiameter (QAngle actualAngle, QAngle calculatedAngle, double actualTicks, QLength wheelDiameter, double ticksPerRotation, QLength trackDiameter) {
    // diameter of the left and right wheels
    cout << "Current diameter of the wheelTrack is " << displayQLength(trackDiameter) << unitType << "\n";

    /**
     * Put the code for calculating the new wheel track here
     * 
     * You should be able to accomplish this with the math here: 
     * Also, use the graph linked above to determine if your program is working properly.
     * 
     * https://www.desmos.com/calculator/7dq6i84ugm
     */
    // Step 1. Calculate the distance with getAndLogCalculatedDistance
    QLength calculatedDistance = 0 * meter;

    cout << "calculatedAngle: " << displayQAngle(calculatedAngle) 
         << " should be close to the actualAngle: " << displayQAngle(actualAngle) << "\n";

    // Step 2. Calculate the newTrackDiameter to set the actualTicks to a certain angle
    QLength newTrackDiameter = 0 * meter;

    cout << "If you change the trackDiameter: " << displayQLength(trackDiameter) << unitType 
         << " to the newTrackDiameter " << displayQLength(newTrackDiameter) << unitType
         << " then if you ROTATE your robot " << actualTicks
         << " ticks the robot should calculate that it rotated: " << displayQAngle(actualAngle) << "\n";
    
    return newTrackDiameter;
}

void tuneFnc (void *params) {
    // The scales are automatically calculated for you in robot.cpp line 136-287
    // we can acces them with the following line of code

    // the straight scale is equal to the ticksPerRotation divided by the wheelDiameter * PI
    ChassisScales scales = drive->getChassisScales(); // This uses the ChassisController defined in robot.h line 26 to get the scales set in robot.cpp line 136-287 https://okapilib.github.io/OkapiLib/classokapi_1_1ChassisController.html#a0a8e32fc7adad8567f550954505aaa06
    // For how to use the ChassisScales class, see https://okapilib.github.io/OkapiLib/classokapi_1_1ChassisScales.html

    // This gets the sensor values of the encoders in the drive's model (normall the SkidSteerModel https://okapilib.github.io/OkapiLib/classokapi_1_1SkidSteerModel.html)
    valarray<int32_t> sensorValsReset = drive->getModel() // This uses the ChassisController drive to get the SkidSteerModel https://okapilib.github.io/OkapiLib/classokapi_1_1ChassisController.html#a1971d4b54b61718437824c026aca53c9
        ->getSensorVals(); // This returns an array of with the sensor values https://okapilib.github.io/OkapiLib/classokapi_1_1SkidSteerModel.html#a850e4de7ab3a30a354ac39f30a1e8603
        // sensorValsReset[0] = current leftEncoder ticks
        // sensorValsReset[1] = current rightEncoder ticks
        // sensorValsReset[2] = current middleEncoder ticks (if there is a 3rd encoder. Most of the time there won't be)

    bool isDisabled = false;
    
    
    double lastTime = pros::millis();// = 0
    pros::delay(50);
    double time = pros::millis();// = 50
    double deltaTime = (time - lastTime)/1000;

    while (!isDisabled) {
        time = pros::millis();
        deltaTime = (time - lastTime)/1000;
        
        // Set the sensorVals to the current sensorVals minus the sensorValsReset
        valarray<int32_t> sensorVals = drive->getModel()->getSensorVals() - sensorValsReset; // by subtracting the current sensorVals by the resetSensorVals, you can reset the sensors at any time by setting the sensorValsReset to the current sensorVals

        int sensorIndex = 0; // 0 is leftEncoder, 1 is rightEncoder, 2 middleEncoder (if using one)
        bool wheelDiameterMode = false;

        if (wheelDiameterMode) {
            // Calculate and log the calculatedDistance and ticks
            QLength calculatedDistance = getAndLogCalculatedDistance(sensorVals[sensorIndex], scales.wheelDiameter, scales.tpr);

            // Change this based on how far you move. The more accurately you move this distance, the more accurate your robot will be.
            QLength actualDistance = 24_in; // 60.96_cm is about 1 tile or 24_in

            // if the a button got pressed, it is assumed that you moved the robot actualDistance since the start of the program, so it will display the newWheelDiameter
            if (a.changedToPressed()) {
                // call calculateNewWheelDiameter (this returns the newWheel distance, but it also logs it)
                calculateNewWheelDiameter(actualDistance, calculatedDistance, sensorVals[sensorIndex], scales.wheelDiameter, scales.tpr);

                isDisabled = true;
            }
        } else {
            // Calculate and log the calculatedDistance and ticks
            QAngle calculatedAngle = getAndLogCalculatedAngle(sensorVals[sensorIndex], scales.wheelDiameter, scales.tpr, scales.wheelTrack);

            // Change this based on how far you move. The more accurately you move this distance, the more accurate your robot will be.
            QAngle actualAngle = 360_deg; // 360_deg, but even better is 1800_deg or 5 rotations

            // if the a button got pressed, it is assumed that you moved the robot actualAngle since the start of the program, so it will display the newTrackDiameter
            if (a.changedToPressed()) {
                // call calculateNewWheelDiameter (this returns the newTrackDiameter distance, but it also logs it)
                calculateNewTrackDiameter(actualAngle, calculatedAngle, sensorVals[sensorIndex], scales.wheelDiameter, scales.tpr, scales.wheelTrack);

                isDisabled = true;
            }
        }
        
        lastTime = pros::millis();
        pros::delay(50);
    }
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
    pros::lcd::initialize();
    pros::lcd::set_text(1, "Hello World!");

    tuneTask = pros::c::task_create(tuneFnc, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "tune task");
}

void disabled() {}
void competition_initialize() {}

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

        while (true) {
                // Split Arcade drive more control over robot see: https://okapilib.github.io/OkapiLib/classokapi_1_1SkidSteerModel.html#aa9b68af25f8f924117b07a5c8e9f6c93
                drive->getModel()->driveVector(master->getAnalog(ControllerAnalog::rightY),
                                               master->getAnalog(ControllerAnalog::leftX));

                pros::delay(10);
        }
}