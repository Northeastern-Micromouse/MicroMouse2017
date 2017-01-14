#include <iostream>
#include "cell.h"

Cell::Cell(int x, int y) {
	x_loc_ = x;
	y_loc_ = y;
	visited_ = false;
}

Cell::Cell() {
	Cell(0,0);
}

int Cell::x() {
	return x_loc_;
}

int Cell::y() {
	return y_loc_; 
}

bool Cell::isVisited() {
	return visited_;
}

void Cell::VisitCell() {
  std::cout << "Visit cell -_- X: " << x_loc_ << " Y: " << y_loc_ << std::endl;
	visited_ = true;
  // For now just return all the directions.
  // TODO(matt): Query the seneors here.
  neighbors_.push_back(RelativeDirection::FORWARD);
  neighbors_.push_back(RelativeDirection::BACKWARD);
  neighbors_.push_back(RelativeDirection::LEFT);
  neighbors_.push_back(RelativeDirection::RIGHT);
}

void Cell::UnVisitCell() {
	visited_ = false;
  neighbors_.clear();
}

std::vector<Cell::RelativeDirection> Cell::GetNeighbors() {
  return neighbors_;
}

std::string Cell::print() {
  // TODO(matt): Implement
  return "";
}
