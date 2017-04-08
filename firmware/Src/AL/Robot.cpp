#include "Robot.h"
#include "stm32l4xx_hal_def.h"
#include "SensorLookupTables.h"
#include <algorithm>

namespace {
    // distance between the two reflectance sensors
    float SIDE_REFL_WIDTH = 92.6;
    float CENTER_TO_WALL_HORIZ = 37.7;
    float CENTER_TO_WALL_VERT = 31.0;
    float CENTER_HORIZ = 84.0;
    
    // The amount of points at which to sample the Hermite spline
    const int SPLINE_SEGMENTS = 10;
    	
    // The number of discrete segments to divide each Hermite spline
    // segment into
    const int SPLINE_ARC_SEGMENTS = 5;
    	
    // The amount of times the PID should be updated during a drive
    const int PID_UPDATES = 5;
    	
    // PID gains
    const float PID_KP = 0.05;
    const float PID_KI = 0.001;
    const float PID_KD = 0.01;
    	
    // Conversion between the special spline units and mm
    const float SPLINE_UNITS_PER_MM = 1.0 / 100;
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
    
    // Manage a PID controller, where the process variable is the horizontal
    // offset within a cell and the output will determine the additional steps
    // to be taken by a side
    util::PID pid(PID_KP, PID_KI, PID_KD);
    pid.Set(target_angle_);
    
    // This represents the distance we've actually travelled in the direction we want to go
    float contributed_distance = 0;
    HAL_Delay(1);
    
    float contr_amt = 0;
    
    for (int i = 0; i < PID_UPDATES; i++) {
        
        // First, update the controller with current information
        float offset = pid.Update(GetHorizontalLocation(true, true), 
            (distance / PID_UPDATES) / velocity);
        
        float left_distance = distance / PID_UPDATES + offset;
        float right_distance = distance / PID_UPDATES - offset;
        
        drive_system_->DriveRelative(left_distance, right_distance, velocity);
        
        //float heading;
        //imu_->GetHeading(heading);
        //heading = util::DeltaAngle(0, heading);
        //contr_amt += (distance / PID_UPDATES) * cos(heading * M_PI / 180.0);
    }
    
    // Update our contributed distance using heading
    //float final_heading;
    //imu_->GetHeading(final_heading);
    //final_heading = util::DeltaAngle(0, final_heading);
    
   // contributed_distance = ((distance) / 2.0) * cos(initial_heading * M_PI / 180.0) + 
     //                       ((distance) / 2.0) * cos(final_heading * M_PI / 180.0);
    
    // Now correct for any less distance travelled
    //SimpleDrive(distance - contributed_distance, velocity);
    
}

void al::Robot::DiscreteSplineDrive(float velocity) {
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
    float starting_x = (31 - GetHorizontalLocation(true, true)) * SPLINE_UNITS_PER_MM;
  
    float left_path[SPLINE_SEGMENTS];
    float right_path[SPLINE_SEGMENTS];
    
    for (int i = 0; i < SPLINE_SEGMENTS; i++) {
        left_path[i] = 
            util::HermiteSplineArcLength(
                starting_x, 
                -drive_system_->GetWidth() * SPLINE_UNITS_PER_MM / 2.0,
                i*spline_step,
                (i + 1)*spline_step,
                SPLINE_ARC_SEGMENTS
            );
        
        right_path[i] =
            util::HermiteSplineArcLength(
                starting_x, 
                drive_system_->GetWidth() * SPLINE_UNITS_PER_MM / 2.0,
                i*spline_step,
                (i + 1)*spline_step,
                SPLINE_ARC_SEGMENTS
            );
    }
    
    HAL_Delay(1);
    
    // Now our path is populated, travel it
    for (int i = 0; i < SPLINE_SEGMENTS; i++) {
        drive_system_->DriveRelative(left_path[i] / SPLINE_UNITS_PER_MM,
                                     right_path[i] / SPLINE_UNITS_PER_MM,
                                     velocity);
    }
}
		
void al::Robot::Turn(int degrees, float angular_velocity) {
    target_angle_ = (target_angle_ + degrees) % 360;
    drive_system_->Turn(degrees * M_PI / 180.0, angular_velocity);
}

phil::DriveSystem* al::Robot::GetDriveSystem() const {
    return drive_system_;
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
