#include "MazeImpl.h"
#include <math.h>

namespace maze {
namespace impl {

using maze::cell::Cell;
using maze::cell::Cell::RelativeDirection::NORTH;
using maze::cell::Cell::RelativeDirection::SOUTH;
using maze::cell::Cell::RelativeDirection::EAST;
using maze::cell::Cell::RelativeDirection::WEST;
using maze::cell::Cell::RelativeDirection::NONE;

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
    if (dir == NONE) {
      continue;
    }
    if (dir == WEST) {
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
      case NORTH:
        return this->operator()(x, y + 1);
      case SOUTH:
        return this->operator()(x, y - 1);
      case WEST:
        return this->operator()(x - 1, y);
      case EAST:
        return this->operator()(x + 1, y);
      case NONE:
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
  if (direction == WEST) {
    dest_x = x - 1;
  }
  else if(direction == EAST) {
    dest_x = x + 1;
  }
  else if(direction == SOUTH) {
    dest_y = y - 1;
  }
  else if(direction == NORTH) {
    dest_y = y + 1;
  }
  else {
    dest_x = x;
    dest_y = y;
  }
  if (dest_x <= 0 && direction == WEST) {
    return false;
  }
  if (dest_x >= maze_size - 1 && direction == EAST) {
    return false;
  }
  if (dest_y >= maze_size - 1  && direction == NORTH) {
    return false;
  }
  return (dest_y <= 0 && direction == SOUTH);
}

}  // impl
}  // maze
