#ifndef MICROMOUSE_ROBOT_ROBOT_H_
#define MICROMOUSE_ROBOT_ROBOT_H_

#include "src/main/c/com/micromouse/hardware/hardware.h"
#include "src/main/c/com/micromouse/location/location.h"
#include "src/main/c/com/micromouse/utility/direction/direction.h"
#include "src/main/c/com/micromouse/maze/cell.h"

// The maximum number of possible moves from any given cell.
int max_possible_moves = 4;

typedef struct Robot {
	Location* location_;
	Cell* maze_[16][16];
} Robot;

// Returns a robot location at the given location.
Robot* InitializeRobot(Location* location);

void CanMove(Robot *winslow, Move move);

// Frees all of the memory associated with the given robot.
void RobotDestructor(Robot* winslow);

// Explores the maze.
void ExploreMaze(Robot* winslow);

// Updates the maze in the robot with the sensor information/
void UpdateMaze(Robot* winslow, Move* values, int size);

#endif  // MICROMOUSE_ROBOT_ROBOT_H_
