#ifndef ROBOT_H
#define ROBOT_H

namespace al
{
	class Robot
	{
	private:
		
		// Represents the distance taken by one step
		const float STEP_DISTANCE = 0;
		
		// Represents the distance between the wheels
		const float ROBOT_WIDTH = 0;
		
		void simpleDrive(float velocity);
		void directedDrive(float velocity);
		void discreteSplineDrive(float velocity);
		void continuousSplineDrive(float velocity);
		
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
		void drive(int nCells, float velocity, DriveMethod method);
		
		void turn(int degrees);
		
		/**** PHYSICAL MEASUREMENT FUNCTIONS ****/
		
	};
}

#endif