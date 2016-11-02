#ifndef CC_ROBOT_IMPL_ROBOTIMPL_H_
#define CC_ROBOT_IMPL_ROBOTIMPL_H_

#include "robot/robot.h"

class RobotImpl : public Robot {
 public:
  RobotImpl();

  void StartExploration() override;

  void ComputeFastestPath() override;

  void GoToGoal() override;
};


#endif  // CC_ROBOT_IMPL_ROBOTIMPL_H_
