#include "MazeImpl.h"
#include <math.h>

namespace maze {
namespace impl {

using maze::cell::Cell;

MazeImpl::MazeImpl() {
  maze_.resize(maze_size * maze_size);
  int count = 0;
  for (std::vector<Cell *>::iterator iter = maze_.begin(); iter != maze_.end(); iter++) {
    *iter = new Cell(count % maze_size, count / maze_size);
    count++;
  }
}

std::vector<Cell *> MazeImpl::GetNeighbors(int x, int y) {
  std::vector<Cell *> neighbors;
  std::vector<Cell::RelativeDirection> directions = this->operator()(x, y)->GetNeighbors();
  for (auto dir : directions) {
    if (dir == Cell::RelativeDirection::NONE) {
      continue;
    }
    if (dir == Cell::RelativeDirection::WEST) {
      std::cout << "WEST" << std::endl;
    }
    Cell *c;
    if ((c = getCell(x, y, dir)) != nullptr) {
      neighbors.push_back(c);
    }
  }
  std::cout << "The size of the neighbors is: " << neighbors.size() << std::endl;
  return neighbors;
}

Cell * MazeImpl::getCell(int x, int y, Cell::RelativeDirection direction) {
  if (!validMove(x, y, direction)) {
    return nullptr;
  }
  try {
    switch (direction) {
      case Cell::RelativeDirection::NORTH:
        return this->operator()(x, y + 1);
      case Cell::RelativeDirection::SOUTH:
        return this->operator()(x, y - 1);
      case Cell::RelativeDirection::WEST:
        return this->operator()(x - 1, y);
      case Cell::RelativeDirection::EAST:
        return this->operator()(x + 1, y);
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

bool MazeImpl::validMove(int x, int y, Cell::RelativeDirection direction) {
  int dest_x = x;
  int dest_y = y;
  if (direction == Cell::RelativeDirection::WEST) {
    dest_x = x - 1;
  }
  else if(direction == Cell::RelativeDirection::EAST) {
    dest_x = x + 1;
  }
  else if(direction == Cell::RelativeDirection::SOUTH) {
    dest_y = y - 1;
  }
  else if(direction == Cell::RelativeDirection::NORTH) {
    dest_y = y + 1;
  }
  else {
    dest_x = x;
    dest_y = y;
  }
  if (dest_x <= 0 && direction == Cell::RelativeDirection::WEST) {
    return false;
  }
  if (dest_x >= maze_size - 1 && direction == Cell::RelativeDirection::EAST) {
    return false;
  }
  if (dest_y >= maze_size - 1  && direction == Cell::RelativeDirection::NORTH) {
    return false;
  }
  return (dest_y <= 0 && direction == Cell::RelativeDirection::SOUTH);
}

}  // impl
}  // maze
