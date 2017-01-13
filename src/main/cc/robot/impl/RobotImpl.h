#ifndef CC_ROBOT_IMPL_ROBOTIMPL_H_
#define CC_ROBOT_IMPL_ROBOTIMPL_H_

#include <stack>
#include "robot/robot.h"
#include "maze/impl/MazeImpl.h"
#include "util/Location.h"

class RobotImpl : public Robot {
 public:
  RobotImpl();

  void StartExploration() override;

  void ComputeFastestPath() override;

  void GoToGoal() override;

 private:
  MazeImpl maze_;
  Location curr_loc_ = Location(0, 0);
  Location goal_ = Location(8, 8);
  std::stack<Cell *> stack_;

  void ReturnToStart();
  void GoBack(Cell::Direction dir);
  std::vector<Cell *> GetNeighbors();
  void VisitCurrentCell();
  void Move(Cell::Direction dir);
  Cell::Direction GetDirection(Cell* cell);
};


#endif  // CC_ROBOT_IMPL_ROBOTIMPL_H_
