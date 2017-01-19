#include <stdio.h>
#include "src/main/c/com/micromouse/robot/robot.h"
#include "src/main/c/com/micromouse/location/location.h"

int main(int argc, char *argv[]) {
  printf("Hello and welcome to Micromouse.\n");
  Location *location = InitializeLocation(0,0);
  Robot *winslow = InitializeRobot(location);
  ExploreMaze(winslow);
  return 0;
}

