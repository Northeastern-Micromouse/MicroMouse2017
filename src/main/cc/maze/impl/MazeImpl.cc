#include "MazeImpl.h"
#include <math.h>

MazeImpl::MazeImpl() {
	maze_.resize(256);
  int count = 0;
  for (std::vector<Cell *>::iterator iter = maze_.begin(); iter != maze_.end(); iter++) {
    *iter = new Cell(count % 16, count / 16);
    count++;
  }
}

std::vector<Cell *> MazeImpl::GetNeighbors(int row, int col) {
	std::vector<Cell *> neighbors;
  std::vector<Cell::RelativeDirection> directions = this->operator()(row, col)->GetNeighbors();
  for (auto dir : directions) {
    std::cout << " Matt" << std::endl;
    neighbors.push_back(getCell(row, col, dir));
  }
  std::cout << "The size of the neighbors is: " << neighbors.size() << std::endl;
  return neighbors;
}

Cell * MazeImpl::getCell(int row, int col, Cell::RelativeDirection direction) {
  // TODO(matt): If you are on an edge this will throw a range error. Fix that.
  try {
    switch (direction) {
      case Cell::RelativeDirection::FORWARD:
        return this->operator()(row, col + 1);
      case Cell::RelativeDirection::BACKWARD:
        return this->operator()(row, col - 1);
      case Cell::RelativeDirection::LEFT:
        return this->operator()(row - 1, col);
      case Cell::RelativeDirection::RIGHT:
        return this->operator()(row + 1, col + 1);
      case Cell::RelativeDirection::NONE:
        // TODO(matt): error checking
        return nullptr;
      default:
        // TODO(matt): error checking
        return nullptr;
    }
  } catch (const std::range_error &ex) {
    std::cout << ex.what() << std::endl;
  }
}
