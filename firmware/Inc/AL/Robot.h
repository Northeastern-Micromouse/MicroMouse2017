#ifndef ROBOT_H
#define ROBOT_H

#include "Motor.h"
#include <math.h>

namespace al
{
	class Robot
	{
	private:
    	
    	phil::Motor left_, right_;
		
		// The distance between the wheels in cm
		const float ROBOT_WIDTH = 0;
    	
    	// The diameter of the wheels in cm
    	const float WHEEL_RADIUS = 0;
    	
    	// The increment amount for traversing the path of the Hermite spline
    	const float SPLINE_STEP = 0.01;
    	
    	// Radians/step of the motors
    	const float RADIANS_PER_STEP = 0;
    	
    	// The distance taken by one step 
    	const float DISTANCE_PER_STEP = WHEEL_RADIUS * RADIANS_PER_STEP;
    	
    	// The distance the left and right motors must travel to rotate the bot
    	// by one degree
    	// = (cm/rad_of_bot_rotation) * (rad/deg) = cm/deg
    	const float ARC_LENGTH_PER_DEGREE = (ROBOT_WIDTH / 2.0) * (M_PI/180.0);
    	
    	// Steps per cell
    	const uint32_t STEPS_PER_CELL = (uint32_t)(18.0 / DISTANCE_PER_STEP);
		
		void SimpleDrive(float velocity);
		void DirectedDrive(float velocity);
		void DiscreteSplineDrive(float velocity);
		void ContinuousSplineDrive(float velocity);
		
	public:
    	
    	Robot(phil::Motor& left, phil::Motor& right);
		
		/**** PHYSICAL CONTROL FUNCTIONS ****/
		
		enum class DriveMethod 
		{
			// Simply drives straight one cell
			SIMPLE,
			
			// Determines the current location within the cell and drives in a
			// straight line toward the midpoint of the next cell, performing a
			// discrete rotation at the beginning and end of motion
			DIRECTED, 
			
			// Calculates a Hermite spline to represent the path to the next
			// cell. The tangent at the start and end points are straight
			// lines pointing straight, while the tangent in the middle is the
			// line connecting the start and endpoints.
			DISCRETESPLINE,
			
			// Similar to discrete spline, except the spline is continously
			// recomputed during the drive based on the current location of the
			// bot in the cell and its current orientation. Computation will
			// only occur if we can obtain an accurate current reading of our
			// horizontal distance between the walls, determined by the current
			// angle of the bot (since if the bot's path is not close to being
			// parallel to the walls, it is hard to get an accurate reading
			// from the reflectance sensors).
			CONTINUOUSSPLINE
		};
		
		// Drives the given number of cells using the given method at the given
		// velocity (in cm/s).
		void Drive(int nCells, float velocity, DriveMethod method);
		
		void Turn(float degrees, float angularVelocity);
		
		/**** PHYSICAL MEASUREMENT FUNCTIONS ****/
		
	};
}

#endif