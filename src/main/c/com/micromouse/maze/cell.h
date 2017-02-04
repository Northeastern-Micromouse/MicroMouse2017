#ifndef MICROMOUSE_MAZE_MAZE_H_
#define MICROMOUSE_MAZE_MAZE_H_

#include "src/main/c/com/micromouse/location/location.h"
#include <stdio.h>
#include <stdbool.h>

// A struct used to represent a cell. The cells orientation is relative to
// its creators position when it entered the maze. I.e. if winslow entered the 
// maze in the south east corner facing towards the north east corner. Then
// The north position in the cell (0,0) is the cell (0,1).
typedef struct Cell {
	// The coordinates of the cell relative to the world.
	Location* location;
	// Whether or not it is possible to reach the cell. 
	// I.e if a cell is surrounded by 4 walls.
	bool open; 

	// True if there is no wall in the square above this cell. 
	bool north;
	// True if there is no wall in the square belove this cell.
	bool south;
	// True if there is no wall in the square to the east of this cell.
	bool east;
	// True if there is no wall in the square to the west of this cell.
	bool west;

	// True if winslow has been to this cell. Used only in finding the 
	// shortest path.
	bool visited;
	// True if winslow has mapped this cell. Used only in mapping the maze.
	bool mapped;

	// parent for the BFS algorithm
	struct Cell* parent;
} Cell;

// Returns true if the given cells are equal, false otherwise
bool SameCell(Cell *, Cell *);

// Determines if the cell is open. Returns true if it is open, false otherwise.
bool DetermineIfOpen(Cell* cell);

void PrintCell(Cell* cell);

// Returns the cells location.
Location *GetLocation(Cell* cell);

// Initializes a cell to all of the default values.
Cell *InitializeCell(int x, int y);

// Frees all of the memory for the given cell.
void CellDestructor(Cell* cell);

#endif  // MICROMOUSE_MAZE_MAZE_H_
