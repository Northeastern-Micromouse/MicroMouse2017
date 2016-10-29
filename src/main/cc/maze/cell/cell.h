#ifndef CC_CELL_CELL_H_
#define CC_CELL_CELL_H_

// Cell class
class Cell {
	// Creates a Cell object at (x,y)
	Cell(int x, int y);

	// Gets the x offsest of a Cell
	int GetLocationX();

	// Gets the y offset of a Cell
	int GetLocationY();

	// Gets the status of whether a Cell has been visited
	bool IsVisited();

	// Marks a Cell as visited
	void VisitCell();

	// Marks a Cell as not visited 
	void unVisitCell();

private:
	int x_loc_;
	int y_loc_; 
	bool visited; 
};

#endif 