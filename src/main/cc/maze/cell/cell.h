#ifndef CC_CELL_CELL_H_
#define CC_CELL_CELL_H_

#include <vector>

// Cell class
class Cell {
public:
	enum Direction {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		NONE
	};

	Cell();

	// Constructs a cell at the given location (x,y).
	Cell(int x, int y);

	// Gets the x offset of a Cell.
	int GetLocationX();

	// Gets the y offset of a Cell.
	int GetLocationY();

	// Gets the status of whether a Cell has been visited.
	bool IsVisited();

	// Visits the cell.
	void VisitCell();

	// UnVisits the cell.
	void UnVisitCell();

	std::vector<Cell::Direction> GetNeighbors();

private:
	int x_loc_;
	int y_loc_; 
	bool visited; 
};

#endif 
