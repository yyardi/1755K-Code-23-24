#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

//Initialize Ports
char DIGITAL_SENSOR_PORT_WINGS = 'A';
char DIGITAL_SENSOR_PORT_FBAR = 'B';
int CATA_PORT = 8;
int INTAKE_PORT = 7;


pros::Motor cata (CATA_PORT, MOTOR_GEARSET_36);
pros::Motor intake (INTAKE_PORT, MOTOR_GEARSET_18);
pros::ADIDigitalOut wings (DIGITAL_SENSOR_PORT_WINGS);
pros::ADIDigitalOut fourBar (DIGITAL_SENSOR_PORT_FBAR);

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(10, 0, 100);
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}


///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}




///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .
void farSideAuton() {
    //START ROBOT WITH INTAKE FACING TOWARDS OUR COLOR BAR
    //if we are blue, the red goal is near us (red -> blue goal)
    //blue start coords: 35.2, 134.6
    chassis.pid_drive_set(32_in, DRIVE_SPEED);
    chassis.pid_wait();

    intake.move_velocity(200);
    pros::delay(1000);
    intake.brake();

    chassis.pid_drive_set(-32_in, DRIVE_SPEED);
    chassis.pid_wait();

    chassis.pid_turn_set(-140_deg, TURN_SPEED); //INTAKE SHOULD BE FACING THE TRIBALL
    chassis.pid_wait();

    wings.set_value(true);
    chassis.pid_drive_set(30_in, DRIVE_SPEED);
    chassis.pid_wait();

    chassis.pid_turn_set(-37_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(30_in, DRIVE_SPEED);
    chassis.pid_wait();

    //Outtake second triball
    intake.move_velocity(-200);
    pros::delay(1500);
    intake.brake();

    wings.set_value(false);
    chassis.pid_drive_set(-21_in, DRIVE_SPEED);
    chassis.pid_wait();

    //HERE WE SHOULD TRY TO GET A SWING
    chassis.pid_turn_set(75_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(55_in, DRIVE_SPEED);
    chassis.pid_wait();
    
    intake.move_velocity(200);
    pros::delay(1000);
    intake.brake();

    chassis.pid_turn_set(-90_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(20_in, DRIVE_SPEED);
    chassis.pid_wait();

    chassis.pid_turn_set(-40_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(20_in, DRIVE_SPEED);
    chassis.pid_wait();

    intake.move_velocity(-200);
    pros::delay(1500);
    intake.brake();

    chassis.pid_drive_set(-23_in, DRIVE_SPEED);
    chassis.pid_wait();

}

