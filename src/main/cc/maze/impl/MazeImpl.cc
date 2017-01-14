#include "MazeImpl.h"
#include <math.h>

MazeImpl::MazeImpl() {
	maze_.resize(maze_size * maze_size);
  int count = 0;
  for (std::vector<Cell *>::iterator iter = maze_.begin(); iter != maze_.end(); iter++) {
    *iter = new Cell(count % maze_size, count / maze_size);
    count++;
  }
}

std::vector<Cell *> MazeImpl::GetNeighbors(int row, int col) {
	std::vector<Cell *> neighbors;
  std::vector<Cell::RelativeDirection> directions = this->operator()(row, col)->GetNeighbors();
  for (auto dir : directions) {
    if (dir == Cell::RelativeDirection::NONE) {
      continue;
    }
    if (getCell(row, col, dir) != nullptr) {
      neighbors.push_back(getCell(row, col, dir));
    }
  }
  std::cout << "The size of the neighbors is: " << neighbors.size() << std::endl;
  return neighbors;
}

Cell * MazeImpl::getCell(int row, int col, Cell::RelativeDirection direction) {
  if (!validMove(row, col, direction)) {
    return nullptr;
  }
  try {
    switch (direction) {
      case Cell::RelativeDirection::NORTH:
        return this->operator()(row, col + 1);
      case Cell::RelativeDirection::SOUTH:
        return this->operator()(row, col - 1);
      case Cell::RelativeDirection::WEST:
        return this->operator()(row - 1, col);
      case Cell::RelativeDirection::EAST:
        return this->operator()(row + 1, col + 1);
      case Cell::RelativeDirection::NONE:
        throw std::range_error("Invalid direction None in getCell");
      default:
        throw std::range_error("Invalid direction in getCell");
    }
  } catch (const std::range_error &ex) {
    std::cout << ex.what() << std::endl;
  }
  return nullptr;
}

std::string MazeImpl::print() {
  // TODO(matt): Implement
  return "";
}

bool MazeImpl::validMove(int row, int col, Cell::RelativeDirection direction) {
  if (row == 0 && direction == Cell::RelativeDirection::SOUTH) {
    return false;
  }
  if (row == maze_size - 1 && direction == Cell::RelativeDirection::NORTH) {
    return false;
  }
  if (col == maze_size - 1  && direction == Cell::RelativeDirection::EAST) {
    return false;
  }
  if (col == 0 && direction == Cell::RelativeDirection::WEST) {
    return false;
  }
  return true;
}
