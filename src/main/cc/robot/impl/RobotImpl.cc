#include <queue>
#include <iostream>
#include "src/main/cc/maze/impl/MazeImpl.h"
#include "RobotImpl.h"

namespace robot {
namespace impl {

using maze::cell::Cell;
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
  Cell::RelativeDirection prev_move = Cell::RelativeDirection::NONE;

  // Visit the first cell.
  VisitCurrentCell();

  // While there are still possible moves to go.
  while (!stack_.empty()) {
    curr_cell = stack_.top();
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
          // If they are not visited then push them onto the stack to visit later
          if (!neighbor->isVisited()) {
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
    case Cell::RelativeDirection::NORTH:
      Move(Cell::RelativeDirection::SOUTH);
      break;
    case Cell::RelativeDirection::SOUTH:
      Move(Cell::RelativeDirection::NORTH);
      break;
    case Cell::RelativeDirection::EAST:
      Move(Cell::RelativeDirection::WEST);
      break;
    case Cell::RelativeDirection::WEST:
      Move(Cell::RelativeDirection::EAST);
      break;
    default:
      break;
  }
}

std::vector<Cell*> RobotImpl::GetNeighbors() {
  return maze_.GetNeighbors(curr_loc_.x(), curr_loc_.y());
}

void RobotImpl::VisitCurrentCell() {
  Cell* curr_cell = maze_(curr_loc_.x(), curr_loc_.y());
  if (!curr_cell->isVisited()) {
    curr_cell->VisitCell();
    for (Cell* neighbor : GetNeighbors()) {
      if (!neighbor->isVisited()) {
        stack_.push(neighbor);
      }
    }
  }
}

void RobotImpl::Move(Cell::RelativeDirection dir) {
  switch (dir) {
    case Cell::RelativeDirection::NORTH:
      //TODO(matt): Actually move forward
      curr_loc_.update(curr_loc_.x(), curr_loc_.y() + 1);
      break;
    case Cell::RelativeDirection::SOUTH:
      //TODO(matt): Actually move backward
      curr_loc_.update(curr_loc_.x(), curr_loc_.y() - 1);
      break;
    case Cell::RelativeDirection::EAST:
      //TODO(matt): Actually move left
      curr_loc_.update(curr_loc_.x() + 1, curr_loc_.y());
      break;
    case Cell::RelativeDirection::WEST:
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
    return Cell::RelativeDirection::NORTH;
  }
  if (x == curr_loc_.x() && y == curr_loc_.y() - 1) {
    return Cell::RelativeDirection::SOUTH;
  }
  if (x == curr_loc_.x() + 1 && y == curr_loc_.y()) {
    return Cell::RelativeDirection::EAST;
  }
  if (x == curr_loc_.x() - 1 && y == curr_loc_.y()) {
    return Cell::RelativeDirection::WEST;
  }
  // TODO(matt): Implement error checking
  return Cell::RelativeDirection::NONE;
}

std::string RobotImpl::print() {
  // TODO(matt): Implement
  return "";
}

}  // impl
}  // robot
