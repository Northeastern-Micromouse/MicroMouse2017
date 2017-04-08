#ifndef CC_ROBOT_IMPL_ROBOTIMPL_H_
#define CC_ROBOT_IMPL_ROBOTIMPL_H_

#include <stack>
#include "Robot.h"
#include "Algo/robot/Algorobot.h"
#include "Algo/maze/impl/MazeImpl.h"
#include "Algo/util/Location.h"
#include "Algo/maze/cell/cell.h"

namespace robot {
namespace impl {

class RobotImpl : public AlgoRobot {
 public:
  RobotImpl(al::Robot winslow);
  RobotImpl(al::Robot winslow, bool enable_debugging);

  void StartExploration() override;

  void ComputeFastestPath() override;

  void GoToGoal() override;

 private:
  maze::impl::MazeImpl maze_;
  util::location::Location curr_loc_ = util::location::Location(0, 0);
  util::location::Location goal_ = util::location::Location(8, 8);
  std::stack<maze::cell::Cell *> stack_;
  bool enable_debugging_;
  maze::cell::Cell::RelativeDirection orientation_;
  al::Robot winslow_;

  void MakeWinslow();
  void ReturnToStart();
  void GoBack(maze::cell::Cell::RelativeDirection dir);
  std::vector<maze::cell::Cell *> GetNeighbors();
  bool VisitCurrentCell();
  void Move(maze::cell::Cell::RelativeDirection dir);
  void MoveNorth();
  void RealMoveForward();
  void TurnEast();
  void TurnWest();
  void MoveEast();
  void MoveSouth();
  void MoveWest();
  maze::cell::Cell::RelativeDirection GetDirection(maze::cell::Cell* cell);
};


}  // impl
}  // robot

#endif  // CC_ROBOT_IMPL_ROBOTIMPL_H_
