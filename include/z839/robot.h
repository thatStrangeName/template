/**
 * robot.h
 *
 * In this file, declare global variables (how to use extern: https://docs.microsoft.com/en-us/cpp/cpp/extern-cpp?view=msvc-160)
 *
 * see the robot.cpp in /src/team for where these variables are set
 */

// the line below ensures that this header file will only be included once (put this at the top of every header file) https://docs.microsoft.com/en-us/cpp/preprocessor/once?view=msvc-160
#pragma once

// include okapi's library. see documentation here: https://okapilib.github.io/OkapiLib/index.html
#include "okapi/api.hpp"

// using namespace makes it so that you don't have to type okapi::Motor all the time instead you can just type Motor: https://docs.microsoft.com/en-us/cpp/cpp/namespaces-cpp?view=msvc-160
using namespace okapi; // all okapi classes, enums, etc
using namespace okapi::literals; // allows you to use
using namespace std;


/** Robot Sub Systems (intake, lift, etc) **/
extern shared_ptr<Motor> lift; // can either Motor or MotorGroup
extern MotorGroup intake; // can either Motor or MotorGroup

/** Robot drive **/
// find chassis controller and model types here: https://okapilib.github.io/OkapiLib/md_docs_api_chassis.html
extern shared_ptr<ChassisController> drive;

/** Controller **/
extern std::shared_ptr<Controller> master; // the default controller is the controller connected to the brain directly
extern ControllerButton a;
extern ControllerButton b;
extern ControllerButton x;
extern ControllerButton y;
extern ControllerButton r1;
extern ControllerButton r2;
extern ControllerButton l1;
extern ControllerButton l2;
extern ControllerButton up;
extern ControllerButton down;
extern ControllerButton left;
extern ControllerButton right;

/** Cool Stuff **/
// pid controller for the lift
//      world's best PID demo in existence https://www.youtube.com/watch?v=fusr9eTceEo
//      how to program page 13-14: https://github.com/team914/autolib-pdfs/blob/master/pid-controllers.pdf
//      how to program page 1-12: https://github.com/team914/autolib-pdfs/blob/master/pid-controllers.pdf
extern shared_ptr<AsyncPosPIDController> liftController;
