#ifndef CC_ROBOT_ROBOT_H_
#define CC_ROBOT_ROBOT_H_

// Abstract class to represent a robot.
public class Robot {
 public:
	// Given an unknown maze start exploration will map the entire maze.
	// Mapping the maze will find all of the locations of the walls and obstacles.
	virtual void StartExploration() = 0;

	// Given a mapped maze will find the quickest path to the goal.
	virtual void ComputeFastestPath() = 0;

	// Moves the robot to the goal using the path found in ComputeFastestPath.
	virtual void GoToGoal() = 0;
};

#endif  // CC_ROBOT_ROBOT_H_