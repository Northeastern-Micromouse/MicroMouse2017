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
    	const int SPLINE_SEGMENTS = 100;
    	
    	// The number of discrete segments to divide each Hermite spline
    	// segment into
    	const int SPLINE_ARC_SEGMENTS = 5;
    	
    	// The amount of times the PID should be updated during a drive
    	const int PID_UPDATES = 100;
		
	public:
    	
    	Robot(phil::DriveSystem* drive_system);
		
		/**** PHYSICAL CONTROL FUNCTIONS ****/
    	void SimpleDrive(float distance, float velocity);
    	void DirectedDrive(float distance, float velocity);
    	void CorrectiveDrive(float distance, float velocity);
    	void DiscreteSplineDrive(float distance, float velocity);
    	void Turn(float degrees, float angularVelocity);
		
		/**** HIGH-LEVEL PHYSICAL MEASUREMENT FUNCTIONS ****/
    	float GetHorizontalLocation();
    	float GetVerticalLocation();
    	float GetHeading();
    	bool GetNextLeftWall();
    	bool GetNextRightWall();
    	
	};
}

#endif