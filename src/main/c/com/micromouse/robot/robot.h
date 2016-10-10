#ifndef MICROMOUSE_ROBOT_ROBOT_H_
#define MICROMOUSE_ROBOT_ROBOT_H_

#include "src/main/c/com/micromouse/maze/cell.h"
#include "src/main/c/com/micromouse/location/location.h"

typedef struct Robot {
	struct Location location_;
	struct Cell maze_[16][16];
} robot;

#endif  // MICROMOUSE_ROBOT_ROBOT_H_