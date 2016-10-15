#ifndef MICROMOUSE_ROBOT_ROBOT_H_
#define MICROMOUSE_ROBOT_ROBOT_H_

#include "src/main/c/com/micromouse/maze/cell.h"
#include "src/main/c/com/micromouse/location/location.h"

typedef struct Robot {
	Location location_;
	Cell maze_[16][16];
} Robot;

// Returns a robot location at the given location.
Robot * InlitializeRobot(Location location);

// Frees all of the memory associated with the given robot.
void RobotDestructor(Robot * winslow);

#endif  // MICROMOUSE_ROBOT_ROBOT_H_