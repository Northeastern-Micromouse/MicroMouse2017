#include <queue>
#include <iostream>
#include "Algo/robot/impl/RobotImpl.h"
#include "Algo/util/logger.h"

namespace robot {
namespace impl {
namespace {
  util::logger log = util::logger(false, std::cout);
}

using maze::cell::Cell;
using util::location::Location;

RobotImpl::RobotImpl(al::Robot winslow) : enable_debugging_(false),
                         orientation_(Cell::RelativeDirection::NORTH), winslow_(winslow) {
                           // No op.
}

RobotImpl::RobotImpl(al::Robot winslow, bool enable_debugging) : enable_debugging_(enable_debugging),
                                              orientation_(Cell::RelativeDirection::NORTH), winslow_(winslow) {
  log.should_log(true);
                                                  MakeWinslow();
}
    
void RobotImpl::MakeWinslow() {
  // No op. 
}

void RobotImpl::StartExploration() {
  log.log("--------------- Start Exploration ---------------");
  // Make sure the robot starts out at the beginning.
  if (curr_loc_.x() != 0 && curr_loc_.y() != 0) {
    ReturnToStart();
  }
  maze_.clear_maze();
  Cell* curr_cell;
  std::vector<Cell*> neighbors;
  Cell::RelativeDirection prev_move = Cell::RelativeDirection::NONE;

  // Visit the first cell.
  // The left and the right walls are always blocked at the start. The f
  VisitCell(maze_(0,0), 0,0,1);

  while (!stack_.empty()) {
    curr_cell = stack_.top();
    stack_.pop();
    if (!curr_cell->isVisited()) {
      prev_move = GetDirection(curr_cell);
      // Move the robot to the cell.
        Rotate(prev_move);
      int left = winslow_.GetNextLeftWall();
      int right = winslow_.GetNextRightWall();
      int top = 0;
      // If any of the sensor values give bogus values retry.
      while (left == -1 || right == -1 || top == -1) {
        if (left == -1) {
            left = winslow_.GetNextLeftWall();
        }
        if (right == -1) {
            right = winslow_.GetNextRightWall();
        }
      }
      // Visit the cell.
        int x = curr_loc_.x();
        int y = curr_loc_.y();
        switch (prev_move) {
          case Cell::RelativeDirection::NORTH:
            y += 1;
            break;
          case Cell::RelativeDirection::SOUTH:
            y -= 1;
            break;
          case Cell::RelativeDirection::EAST:
            x += 1;
            break;
          case Cell::RelativeDirection::WEST:
            x -= 1;
            break;
          default:
            break;
      } 
        
      Cell* cell = maze_(x, y);
      if (!VisitCell(cell, left, right, top)) {
          Move(prev_move);
      }
    }
  }
}

void RobotImpl::GoToGoal() {
  // TODO(matt): Implement
}

void RobotImpl::ComputeFastestPath() {
  Cell* itr;
  std::queue<maze::cell::Cell *> queue;
  std::vector<maze::cell::Cell*> neighbors = maze_.GetNeighbors(0,0);
  curr_loc_.update(0,0);
  maze_.clear_maze();
  maze_.operator()(0,0)->VisitCell(0,0,0);

  for (Cell* cell : neighbors) {
    cell->setParent(0, 0);
    cell->VisitCell(0,0,0);
    queue.push(cell);
  }

  while (!queue.empty()) {
    itr = queue.front();
    queue.pop();
    if (itr->x() == 8 && itr->y() == 8) {
      break;
    }
    neighbors = maze_.GetNeighbors(itr->x(), itr->y());
    for (maze::cell::Cell* cell : neighbors) {
      if (!cell->isVisited()) {
        cell->setParent(itr->x(), itr->y());
        cell->VisitCell(0,0,0);
        queue.push(cell);
      }
    }
    curr_loc_.update(itr->x(),itr->y());
  }

  curr_loc_.update(8,8);
  util::location::Location temp(0,0);
  while (curr_loc_.x() != 0 || curr_loc_.y() != 0) {
    log.log("At location X: " + std::to_string(curr_loc_.x()) + " Y: " + std::to_string(curr_loc_.y()));
    temp = maze_.operator()(curr_loc_.x(), curr_loc_.y())->getParent();
    log.log("Moving to X: " + std::to_string(temp.x()) + " Y: " + std::to_string(temp.y()));
    curr_loc_.update(temp.x(), temp.y());
  }
}

void RobotImpl::ReturnToStart() {
  // TODO(matt): Implement
  log.log("--------------- Return To Start ---------------");
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

bool RobotImpl::VisitCell(Cell* cell, int left, int right, int top) {
  bool should_move_forward = false;
  if (!cell->isVisited()) {
    log.log("--------------- Visit A Cell ---------------");
    log.log("X: " + std::to_string(cell->x()));
    log.log("Y: " + std::to_string(cell->y()));
    log.log("--------------------------------------------");
    cell->VisitCell(left, right, top);
    for (Cell* neighbor : GetNeighbors()) {
      if (!neighbor->isVisited()) {
        should_move_forward = true;
        stack_.push(neighbor);
      }
    }
  }
  return should_move_forward;
}

void RobotImpl::MoveNorth() {
  if (orientation_ == Cell::RelativeDirection::NORTH) {
    // Do nothing.
  } else if (orientation_ == Cell::RelativeDirection::EAST) {
    Rotate(-90);
  } else if (orientation_ == Cell::RelativeDirection::WEST) {
    Rotate(90);
  } else {
    Rotate(180);
  }
  orientation_ = Cell::RelativeDirection::NORTH;
}

void RobotImpl::MoveEast() {
  if (orientation_ == Cell::RelativeDirection::NORTH) {
    Rotate(90);
  } else if (orientation_ == Cell::RelativeDirection::EAST) {
    // Do nothing.
  } else if (orientation_ == Cell::RelativeDirection::WEST) {
    Rotate(180);
  } else {
    Rotate(-90);
  }
  orientation_ = Cell::RelativeDirection::EAST;
}

void RobotImpl::MoveSouth() {
  if (orientation_ == Cell::RelativeDirection::NORTH) {
    Rotate(180);
  } else if (orientation_ == Cell::RelativeDirection::EAST) {
    Rotate(90);
  } else if (orientation_ == Cell::RelativeDirection::WEST) {
    Rotate(-90);
  } else {
    // Do nothing.
  }
  orientation_ = Cell::RelativeDirection::SOUTH;
}

void RobotImpl::MoveWest() {
  if (orientation_ == Cell::RelativeDirection::NORTH) {
    Rotate(-90);
  } else if (orientation_ == Cell::RelativeDirection::EAST) {
    Rotate(180);
  } else if (orientation_ == Cell::RelativeDirection::WEST) {
    // Do nothing.
  } else {
    Rotate(90);
  }
  orientation_ = Cell::RelativeDirection::WEST;
}

void RobotImpl::Move(Cell::RelativeDirection dir) {
  // TODO(matt): Implement
}

void RobotImpl::Rotate(int degrees) {
  // TODO(matt): Implement
}

void RobotImpl::Rotate(Cell::RelativeDirection dir) {
  switch (dir) {
    case Cell::RelativeDirection::NORTH:
      log.log("--------------- Move from Cell ---------------");
      log.log("X: " + std::to_string(curr_loc_.x()));
      log.log("Y: " + std::to_string(curr_loc_.y()));
      log.log("----------------------------------------------");
      curr_loc_.update(curr_loc_.x(), curr_loc_.y() + 1);
      log.log("--------------- to Cell ---------------");
      log.log("X: " + std::to_string(curr_loc_.x()));
      log.log("Y: " + std::to_string(curr_loc_.y()));
      log.log("----------------------------------------------");
      MoveNorth();
      break;
    case Cell::RelativeDirection::SOUTH:
      // TODO(matt): Actually move backward
      log.log("--------------- Move from Cell ---------------");
      log.log("X: " + std::to_string(curr_loc_.x()));
      log.log("Y: " + std::to_string(curr_loc_.y()));
      log.log("----------------------------------------------");
      curr_loc_.update(curr_loc_.x(), curr_loc_.y() - 1);
      log.log("--------------- to Cell ---------------");
      log.log("X: " + std::to_string(curr_loc_.x()));
      log.log("Y: " + std::to_string(curr_loc_.y()));
      log.log("----------------------------------------------");
      MoveSouth();
      break;
    case Cell::RelativeDirection::EAST:
      // TODO(matt): Actually move left
      log.log("--------------- Move from Cell ---------------");
      log.log("X: " + std::to_string(curr_loc_.x()));
      log.log("Y: " + std::to_string(curr_loc_.y()));
      log.log("----------------------------------------------");
      curr_loc_.update(curr_loc_.x() + 1, curr_loc_.y());
      log.log("--------------- to Cell ---------------");
      log.log("X: " + std::to_string(curr_loc_.x()));
      log.log("Y: " + std::to_string(curr_loc_.y()));
      log.log("----------------------------------------------");
      MoveEast();
      break;
    case Cell::RelativeDirection::WEST:
      // TODO(matt): Actually move right
      log.log("--------------- Move from Cell ---------------");
      log.log("X: " + std::to_string(curr_loc_.x()));
      log.log("Y: " + std::to_string(curr_loc_.y()));
      log.log("----------------------------------------------");
      curr_loc_.update(curr_loc_.x() - 1, curr_loc_.y());
      log.log("--------------- to Cell ---------------");
      log.log("X: " + std::to_string(curr_loc_.x()));
      log.log("Y: " + std::to_string(curr_loc_.y()));
      log.log("----------------------------------------------");
      MoveWest();
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

}  // impl
}  // robot
