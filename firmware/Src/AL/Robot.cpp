#include "Robot.h"
#include "stm32l4xx_hal_def.h"
#include "SensorLookupTables.h"

namespace {
    // distance between the two reflectance sensors
    float SIDE_REFL_WIDTH = 92.6;
    float CENTER_TO_WALL_HORIZ = 37.7;
    float CENTER_TO_WALL_VERT = 31.0;
    float CENTER_HORIZ = 84.0;
}

al::Robot::Robot(phil::DriveSystem* drive_system): 
    drive_system_(drive_system) {}

al::Robot::Robot(
    phil::DriveSystem* drive_system,
    phil::IMU* imu,
    phil::Distance* dist_left,
    phil::Distance* dist_right,
    phil::Reflectance* refl_left,
    phil::Reflectance* refl_right,
    phil::Reflectance* refl_center) :
    drive_system_(drive_system),
    imu_(imu),
    dist_left_(dist_left),
    dist_right_(dist_right),
    refl_left_(refl_left),
    refl_right_(refl_right),
    refl_center_(refl_center) {}

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
    // TODO: add wall parsing before this call VVV
    float starting_x = GetHorizontalLocation(true, true);
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

float al::Robot::GetVerticalLocation() {
    bool max = false;
    float front_sensor_reading = refl_center_->GetDistance(&max);
    float heading = 0;
    if (imu_->GetHeading(heading) != HAL_OK) {
        printf("IMU Read Failed!\n");
        return -1;
    }
    
    float offset = target_angle_;
    if (target_angle_ == 0 && heading >= 270) {
        offset = 360;
    }
    float angle_from_target = heading - offset;
    
    float front_error = CENTER_TO_WALL_VERT - (cos(angle_from_target * (M_PI / 180.0)) * front_sensor_reading);
    return front_error;
}

float al::Robot::GetHorizontalLocation(bool left_wall, bool right_wall) {
    /**
        Params: (bool) left_wall, (bool) right_wall
        Returns: an offset from center in mm on success
                 -1 on operation fail
    **/
    
    if (!left_wall && !right_wall) {
        printf("Cannot calculate, no reference walls\n");
        return -1;
    }
    
    bool left_max = false;
    bool right_max = false;
    float left_sensor_reading = refl_left_->GetDistance(&left_max);
    float right_sensor_reading = refl_right_->GetDistance(&right_max);
    float heading = 0;
    if (imu_->GetHeading(heading) != HAL_OK) {
        printf("IMU Read Failed!\n");
        return -1;
    }
    
    float offset = target_angle_;
    if (target_angle_ == 0 && heading >= 270) {
        offset = 360;
    }
    float angle_from_target = heading - offset;
    
    float left_error = (4 + CENTER_HORIZ) - ((left_sensor_reading + SIDE_REFL_WIDTH / 2) * cos(angle_from_target * (M_PI / 180.0)) + (33.0 * sin(-angle_from_target * (M_PI / 180.0))));
    float right_error = ((right_sensor_reading + SIDE_REFL_WIDTH / 2) * cos(angle_from_target * (M_PI / 180.0)) - (33.0 * sin(-angle_from_target * (M_PI / 180.0)))) - (4 + CENTER_HORIZ);
    
    if (left_wall && right_wall) {
        if (left_max) {
            return right_error;
        }
        if (right_max) {
            return left_error;
        }
        return (left_error + right_error) / 2;
    }
    else if (left_wall) {
        return (left_error);
    }
    else return right_error;
    
    
    
}

int al::Robot::GetNextLeftWall() {
    
    int yes_wall = 0;
    int no_wall = 0;
    float distance = 0;
    for (int i = 0; i < 51; ++i) {
        distance = dist_left_->GetDistance();
        if (distance <= 210) {
            yes_wall++;
        }
        else {
            no_wall++;
        }
    }
    
    if (((float)yes_wall / (yes_wall + no_wall)) >= 0.75) {
        return 1;
    }
    else if (((float)no_wall / (yes_wall + no_wall)) >= 0.75) {
        return 0;
    }
    else return -1;
}

int al::Robot::GetNextRightWall() {
    
    int yes_wall = 0;
    int no_wall = 0;
    float distance = 0;
    for (int i = 0; i < 51; ++i) {
        distance = dist_right_->GetDistance();
        if (distance <= 210) {
            yes_wall++;
        }
        else {
            no_wall++;
        }
    }
    
    if (((float)yes_wall / (yes_wall + no_wall)) >= 0.75) {
        return 1;
    }
    else if (((float)no_wall / (yes_wall + no_wall)) >= 0.75) {
        return 0;
    }
    else return -1;
}