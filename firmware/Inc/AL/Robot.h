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
    	void DiscreteSplineDrive(float velocity);
    	void Turn(int degrees, float angular_velocity);
		
		/**** HIGH-LEVEL PHYSICAL MEASUREMENT FUNCTIONS ****/
    	float GetHorizontalLocation(bool left_wall, bool right_wall);
    	float GetVerticalLocation();
    	float GetHeading();
    	int GetNextLeftWall();
    	int GetNextRightWall();
    	
    	phil::DriveSystem* GetDriveSystem() const;
    	
	};
}

#endif