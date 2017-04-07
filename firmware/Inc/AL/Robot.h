#ifndef ROBOT_H
#define ROBOT_H

#include "DriveSystem.h"
#include "IMU.h"
#include "util.h"
#include "Reflectance.h"
#include "Distance.h"

#include <math.h>

#define CORRECTIVE_DRIVE_POINTS   10

namespace al {
    
	class Robot {
    	
	private:

    	phil::DriveSystem* drive_system_;
    	phil::IMU* imu_;
    	phil::Reflectance* refl_left_;
    	phil::Reflectance* refl_right_;
    	phil::Reflectance* refl_center_;
    	phil::Distance* dist_left_;
    	phil::Distance* dist_right_;
		
    	int target_angle_ = 0;
    	
    	// The amount of points at which to sample the Hermite spline
    	const int SPLINE_SEGMENTS = 100;
    	
    	// The number of discrete segments to divide each Hermite spline
    	// segment into
    	const int SPLINE_ARC_SEGMENTS = 5;
    	
    	// The amount of times the PID should be updated during a drive
    	const int PID_UPDATES = 100;
		
	public:
    	
    	Robot(phil::DriveSystem* drive_system);
		
    	Robot(
            phil::DriveSystem* drive_system,
        	phil::IMU* imu,
        	phil::Distance* dist_left,
        	phil::Distance* dist_right,
        	phil::Reflectance* refl_left,
        	phil::Reflectance* refl_right,
        	phil::Reflectance* refl_center);
    	
    	/**** INIT ****/
    	void Init();
    	
		/**** PHYSICAL CONTROL FUNCTIONS ****/
    	void SimpleDrive(float distance, float velocity);
    	void DirectedDrive(float distance, float velocity);
    	void CorrectiveDrive(float distance, float velocity);
    	void DiscreteSplineDrive(float distance, float velocity);
    	void Turn(float degrees, float angularVelocity);
		
		/**** HIGH-LEVEL PHYSICAL MEASUREMENT FUNCTIONS ****/
    	float GetHorizontalLocation(bool left_wall, bool right_wall);
    	float GetVerticalLocation();
    	float GetHeading();
    	int GetNextLeftWall();
    	int GetNextRightWall();
    	
	};
}

#endif