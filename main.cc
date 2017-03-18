#include <iostream>
#include "src/main/cc/robot/impl/RobotImpl.h"

int main() {
  std::cout << "Starting the program" << std::endl;
  robot::impl::RobotImpl winslow = robot::impl::RobotImpl(true);
  winslow.StartExploration();
  return 0;
}
