#include "Robot.h"

al::Robot::Robot(phil::Motor& left, phil::Motor& right): 
    left_(left), right_(right) {}

void al::Robot::SimpleDrive(float velocity) {
    // First, get and set the angular velocity from linear velocity
    float w = velocity / al::Robot::WHEEL_RADIUS;
    left_.SetAngularVelocity(w, RADIANS_PER_STEP);
    right_.SetAngularVelocity(w, RADIANS_PER_STEP);
    
    // Prepare the motors for simple forward motion
    left_.resetSteps();
    right_.resetSteps();
    left_.SetDirection(phil::Motor::Direction::CCW);
    right_.SetDirection(phil::Motor::Direction::CW);
    left_.SetMotion(true);
    right_.SetMotion(true);
    
    // Drive for 18cm
    while (left_.getSteps() < al::Robot::STEPS_PER_CELL &&
            right_.getSteps() < al::Robot::STEPS_PER_CELL);
    
    left_.SetMotion(false);
    right_.SetMotion(false);
}

void al::Robot::DirectedDrive(float velocity) {
    
}

float HermiteSplineArcLength(float startingPosition, 
                              float t0, float t1, 
                              float offset) {
    // Normally, the equation for the Hermite Spline can be quite long, but 
    // here we will simplify the equation by utilizing the fact that the
    // tangent at both points will be (0,1), the final point will always be
    // (0.5, 1), and the y-coordinate of the starting point is always 0.
    // We will take the offset of this curve (using 0 to represent the regular
    // curve) and calculate the arc length between t0 and t1.
}

void al::Robot::DiscreteSplineDrive(float velocity) {
    // First, use our current horizontal position to compute the parametric
    // Hermite spline
    // Next, take the positive offset curve to represent the path of the right
    // wheel and the negative offset curve to represent the path of the left
    // wheel.
    // Compute the time taken to advance down the spline path by one segment
    // (that is, one multiple of SPLINE_STEP) using the arc length of the
    // current segment and the given velocity.
    // Compute the arc length of the offset curves at the current segment and
    // using the time computer earlier, determine the velocities of each wheel.
    // Convert the linear velocities into angular velocities and set the wheels
    // in motion.
    // Stop travelling when both wheels have reached where they need to be.
    // In order to preserve the "curvy" nature of the spline, we must maximize
    // the turn radius by using small-scale numbers (<= 1). Therefore, all 
    // units for this function and associated functions is "cells".
}

void al::Robot::ContinuousSplineDrive(float velocity) {
    
}

void al::Robot::Drive(int nCells, float velocity, DriveMethod method) {
    
}
		
void al::Robot::Turn(float degrees, float angularVelocity) {
    // First, get the transverse velocity of the robot's rotation from angular
    float velocity = al::Robot::ROBOT_WIDTH * angularVelocity;
    
    // Then, get and set the angular velocity from linear velocity
    float w = velocity / al::Robot::WHEEL_RADIUS;
    left_.SetAngularVelocity(w, RADIANS_PER_STEP);
    right_.SetAngularVelocity(w, RADIANS_PER_STEP);
    
    // Prepare the motors for simple forward motion
    left_.resetSteps();
    right_.resetSteps();
    phil::Motor::Direction motorDir = degrees > 0 ? phil::Motor::Direction::CCW : phil::Motor::Direction::CW;
    left_.SetDirection(motorDir);
    right_.SetDirection(motorDir);
    left_.SetMotion(true);
    right_.SetMotion(true);
    
    while (left_.getSteps() < al::Robot::ARC_LENGTH_PER_DEGREE * degrees &&
            right_.getSteps() < al::Robot::ARC_LENGTH_PER_DEGREE * degrees);
    
    left_.SetMotion(false);
    right_.SetMotion(false);
}
