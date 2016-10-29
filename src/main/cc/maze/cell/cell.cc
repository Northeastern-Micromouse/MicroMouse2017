#include "cell.h"

Cell::Cell(int x, int y) {
	x_loc_ = x;
	y_loc_ = y;
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

void Cell::UnvisitCell() {
	visited = false; 
}