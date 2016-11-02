#include "cell.h"

Cell::Cell(int x, int y) {
	x_loc_ = x;
	y_loc_ = y;
	visited = false; 
}

Cell::Cell() {
	x_loc_ = 0;
	y_loc_ = 0;
	visited = false;
}

int Cell::GetLocationX() {
	return x_loc_;
}

int Cell::GetLocationY() {
	return y_loc_; 
}

bool Cell::IsVisited() {
	return visited; 
}

void Cell::VisitCell() {
	visited = true; 
}

void Cell::UnVisitCell() {
	visited = false;
}
