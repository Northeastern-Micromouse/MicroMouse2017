#include <iostream>
#include "src/main/cc/robot/impl/RobotImpl.h"

int main() {
  std::cout << "Starting the program" << std::endl;
  RobotImpl winslow = RobotImpl();
  winslow.StartExploration();
  return 0;
}
