#include "Robot.h"

al::Robot::Robot(phil::DriveSystem* drive_system): 
    drive_system_(drive_system) {}

void al::Robot::SimpleDrive(float distance, float velocity) {
    drive_system_->DriveStraight(distance, velocity);
}

void al::Robot::DirectedDrive(float distance, float velocity) {
    
}

void al::Robot::CorrectiveDrive(float distance, float velocity) {
    
}

void al::Robot::DiscreteSplineDrive(float distance, float velocity) {
    // First, use our current horizontal position to compute the parametric
    // Hermite spline
    // Next, take the positive offset curve to represent the path of the right
    // wheel and the negative offset curve to represent the path of the left
    // wheel.
    // Use the arc lengths of each curve as arguments to DriveRelative until
    // the entire spline has been travelled.
    // In order to preserve the "curvy" nature of the spline, we must maximize
    // the turn radius by using small-scale numbers (<= 1). Therefore, all 
    // computations within this function are done in "cells".
    
    // First, plan the entire path in an array with the arc lengths
    float spline_step = 1.0 / SPLINE_SEGMENTS;
    float starting_x = GetHorizontalLocation();
    float left_path[SPLINE_SEGMENTS];
    float right_path[SPLINE_SEGMENTS];
    
    for (int i = 0; i < SPLINE_SEGMENTS; i++) {
        left_path[i] = 
            util::HermiteSplineArcLength(
                starting_x, 
                -drive_system_->GetWidth() / 2.0,
                i*spline_step,
                (i+1)*spline_step,
                SPLINE_ARC_SEGMENTS
            );
        
        right_path[i] =
            util::HermiteSplineArcLength(
                starting_x, 
                drive_system_->GetWidth() / 2.0,
                i*spline_step,
                (i + 1)*spline_step,
                SPLINE_ARC_SEGMENTS
            );
    }
    
    // Now our path is populated, travel it
    for (int i = 0; i < SPLINE_SEGMENTS; i++) {
        drive_system_->DriveRelative(left_path[i]*distance, right_path[i]*distance, velocity);
    }
}
		
void al::Robot::Turn(float degrees, float angularVelocity) {
    
}
