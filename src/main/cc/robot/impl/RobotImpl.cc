#include <queue>
#include <iostream>
#include "src/main/cc/maze/impl/MazeImpl.h"
#include "RobotImpl.h"

namespace robot {
namespace impl {

using maze::cell::Cell;
using maze::cell::Cell::RelativeDirection::NORTH;
using maze::cell::Cell::RelativeDirection::SOUTH;
using maze::cell::Cell::RelativeDirection::EAST;
using maze::cell::Cell::RelativeDirection::WEST;
using maze::cell::Cell::RelativeDirection::NONE;
using util::location::Location;

RobotImpl::RobotImpl() {
  // No op.
}

void RobotImpl::StartExploration() {
  std::cout<< "RobotImpl - Start Exploration" << std::endl;
  if (curr_loc_.x() != 0 && curr_loc_.y() != 0) {
    ReturnToStart();
  }
  Cell* curr_cell;
  std::vector<Cell*> neighbors;
  Cell::RelativeDirection prev_move = NONE;

  // Visit the first cell.
  VisitCurrentCell();

  // While there are still possible moves to go.
  while (!stack_.empty()) {
    curr_cell = stack_.top();
    std::cout << "popping cell: " << std::endl;
    curr_cell->print();
    stack_.pop();
    // If it is not visited we need to visit it.
    if (!curr_cell->isVisited()) {
      prev_move = GetDirection(curr_cell);
      // Move the robot to the cell.
      Move(prev_move);
      // Visit the cell.
      curr_cell->VisitCell();
      neighbors = GetNeighbors();
      // If it is empty we cannot go forward any more, so move back.
      if (!neighbors.empty()) {
        // Loop through all of its possible neighbors.
        for (Cell* neighbor : neighbors) {
          std::cout << "Neighbor cell: " << std::endl;
          neighbor->print();
          // If they are not visited then push them onto the stack to visit later
          if (!neighbor->isVisited()) {
            std::cout << "Adding cell: " << std::endl;
            neighbor->print();
            stack_.push(neighbor);
          }
        }
      } else {
        GoBack(prev_move);
      }
    } else {
      // Otherwise we have to move back
      GoBack(prev_move);
    }
  }
}

void RobotImpl::GoToGoal() {
  // TODO(matt): Implement
}

void RobotImpl::ComputeFastestPath() {
  // TODO(matt): Implement
}

void RobotImpl::ReturnToStart() {
  // TODO(matt): Implement
}

void RobotImpl::GoBack(Cell::RelativeDirection dir) {
  switch (dir) {
    case NORTH:
      Move(SOUTH);
      break;
    case SOUTH:
      Move(NORTH);
      break;
    case EAST:
      Move(WEST);
      break;
    case WEST:
      Move(EAST);
      break;
    default:
      break;
  }
}

std::vector<Cell*> RobotImpl::GetNeighbors() {
  return maze_.GetNeighbors(curr_loc_.x(), curr_loc_.y());
}

void RobotImpl::VisitCurrentCell() {
  std::cout << "Visit Current Cell" << std::endl;
  Cell* curr_cell = maze_(curr_loc_.x(), curr_loc_.y());
  std::cout << "Visit Current Cell: X: " << curr_cell->x() <<  " Y: "<< curr_cell->y() << std::endl;
  if (!curr_cell->isVisited()) {
    std::cout << "The Cell is not visited" << std::endl;
    curr_cell->VisitCell();
    for (Cell* neighbor : GetNeighbors()) {
      std::cout << "Have a neighbor of a cell at: " << neighbor->x() << ", " << neighbor->y() << std::endl;
      if (!neighbor->isVisited()) {
        std::cout << "Adding cell" << std::endl;
        neighbor->print();
        stack_.push(neighbor);
      }
    }
  }
}

void RobotImpl::Move(Cell::RelativeDirection dir) {
  switch (dir) {
    case NORTH:
      //TODO(matt): Actually move forward
      curr_loc_.update(curr_loc_.x(), curr_loc_.y() + 1);
      break;
    case SOUTH:
      //TODO(matt): Actually move backward
      curr_loc_.update(curr_loc_.x(), curr_loc_.y() - 1);
      break;
    case EAST:
      //TODO(matt): Actually move left
      curr_loc_.update(curr_loc_.x() + 1, curr_loc_.y());
      break;
    case WEST:
      //TODO(matt): Actually move right
      curr_loc_.update(curr_loc_.x() - 1, curr_loc_.y());
      break;
    default:
      break;
  }
}

Cell::RelativeDirection RobotImpl::GetDirection(Cell* cell) {
  int x = cell->x();
  int y = cell->y();
  if (x == curr_loc_.x() && y == curr_loc_.y() + 1) {
    return NORTH;
  }
  if (x == curr_loc_.x() && y == curr_loc_.y() - 1) {
    return SOUTH;
  }
  if (x == curr_loc_.x() + 1 && y == curr_loc_.y()) {
    return EAST;
  }
  if (x == curr_loc_.x() - 1 && y == curr_loc_.y()) {
    return WEST;
  }
  // TODO(matt): Implement error checking
  return NONE;
}

std::string RobotImpl::print() {
  // TODO(matt): Implement
  return "";
}

}  // impl
}  // robot
