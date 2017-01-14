#include <iostream>
#include "src/main/cc/robot/impl/RobotImpl.h"

int main() {
  std::cout << "Hello Winslow!" << std::endl;
  RobotImpl winslow = RobotImpl();
//  winslow.StartExploration();
  Cell cell = Cell(0, 0);
  cell.print();
  cell.VisitCell();
  cell.print();
  return 0;
}

