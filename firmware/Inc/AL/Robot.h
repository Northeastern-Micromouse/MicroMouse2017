#ifndef ROBOT_H
#define ROBOT_H

#include "DriveSystem.h"
#include "IMU.h"
#include "util.h"
#include <math.h>

#define CORRECTIVE_DRIVE_POINTS   10

namespace al {
    
	class Robot {
    	
	private:
    	
    	phil::DriveSystem* drive_system_;
    	phil::IMU* imu_;
		
    	// The amount of points at which to sample the Hermite spline
    	const int SPLINE_SEGMENTS = 10;
    	
    	// The number of discrete segments to divide each Hermite spline
    	// segment into
    	const int SPLINE_ARC_SEGMENTS = 50;
    	
    	// The amount of times the PID should be updated during a drive
    	const int PID_UPDATES = 10;
    	
    	// PID gains
    	const float PID_KP = 0.1;
    	const float PID_KI = 0;
    	const float PID_KD = 0;
    	
    	// Conversion between the special spline units and mm
    	const float SPLINE_UNITS_PER_MM = 1.0/100;
		
	public:
    	
    	Robot(phil::DriveSystem* drive_system);
		
		/**** PHYSICAL CONTROL FUNCTIONS ****/
    	void SimpleDrive(float distance, float velocity);
    	void DirectedDrive(float distance, float velocity);
    	void CorrectiveDrive(float distance, float velocity);
    	void DiscreteSplineDrive(float velocity);
    	void Turn(float degrees, float angular_velocity);
		
		/**** HIGH-LEVEL PHYSICAL MEASUREMENT FUNCTIONS ****/
    	float GetHorizontalLocation();
    	float GetVerticalLocation();
    	float GetHeading();
    	bool GetNextLeftWall();
    	bool GetNextRightWall();
    	
    	phil::DriveSystem* GetDriveSystem() const;
    	
	};
}

#endif