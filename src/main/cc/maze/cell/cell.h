#ifndef CC_CELL_CELL_H_
#define CC_CELL_CELL_H_

#include <vector>

// Represents a single cell in the micromouse maze.
// A cell has an
//    - x coordinate
//    - y coordinate
//    - a visited flag
//    - A list of relative directions representing its neighbors. Two cells are neighbors of one another if
//    they are reachable by only one movement in the respective relative direction.

class Cell {
public:
	// Represents a relative direction
	enum RelativeDirection {
		NORTH,
		SOUTH,
		EAST,
		WEST,
		NONE
	};

	Cell();

	// Constructs a cell at the given location (x,y).
	Cell(int x, int y);

	// Gets the x offset of a Cell.
	int x();

	// Gets the y offset of a Cell.
	int y();

	// Gets the status of whether a Cell has been visited.
	bool isVisited();

	// Visits the cell.
	void VisitCell();

	// UnVisits the cell.
	void UnVisitCell();

  // Returns the neighbors of the given cell. If the cell has no neighbors the resulting
  // vector is empty.
	std::vector<Cell::RelativeDirection> GetNeighbors();

  void print();

private:
	int x_loc_;
	int y_loc_; 
	bool visited_;
  std::vector<Cell::RelativeDirection> neighbors_;
};

#endif 
