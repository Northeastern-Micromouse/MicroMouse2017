#ifndef CC_ROBOT_IMPL_ROBOTIMPL_H_
#define CC_ROBOT_IMPL_ROBOTIMPL_H_

#include <stack>
#include "src/main/cc/robot/robot.h"
#include "src/main/cc/maze/impl/MazeImpl.h"
#include "src/main/cc/util/Location.h"

namespace robot {
namespace impl {

class RobotImpl : public Robot {
 public:
  RobotImpl();
  RobotImpl(bool enable_debugging);

  void StartExploration() override;

  void ComputeFastestPath() override;

  void GoToGoal() override;

 private:
  maze::impl::MazeImpl maze_;
  util::location::Location curr_loc_ = util::location::Location(0, 0);
  util::location::Location goal_ = util::location::Location(8, 8);
  std::stack<maze::cell::Cell *> stack_;
  bool enable_debugging_;

  void ReturnToStart();
  void GoBack(maze::cell::Cell::RelativeDirection dir);
  std::vector<maze::cell::Cell *> GetNeighbors();
  bool VisitCurrentCell();
  void Move(maze::cell::Cell::RelativeDirection dir);
  maze::cell::Cell::RelativeDirection GetDirection(maze::cell::Cell* cell);
};


}  // impl
}  // robot

#endif  // CC_ROBOT_IMPL_ROBOTIMPL_H_
