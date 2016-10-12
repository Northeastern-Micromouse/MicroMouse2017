#ifndef MICROMOUSE_MAZE_MAZE_H_
#define MICROMOUSE_MAZE_MAZE_H_

#include "src/main/c/com/micromouse/location/location.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct Cell {
	struct Location location;
	bool open; 
	bool top;
	bool bottom;
	bool right;
	bool left;
	bool visited;
	bool mapped;
} cell;

#endif  // MICROMOUSE_MAZE_MAZE_H_
