#include <assert.h>
#include <printf.h>
#include "hardware.h"

void PollSensors(Move* arr, int size) {
	printf("Polling the sensors\n");
  // TODO(matt): Actually do what we should do and not jsut return true for everything.
  for (int i = 0; i < size; i++) {
    arr[i].dir_ = NORTH;
    arr[i].is_valid_ = true;
  }
}

void HardwareMove(direction_t direction) {
  switch (direction) {
    case NORTH:
      printf("Moving north\n");
      // TODO(matt): Implement
      break;
    case SOUTH:
      printf("Moving south\n");
      // TODO(matt): Implement
      break;
    case EAST:
      printf("Moving east\n");
      // TODO(matt): Implement
      break;
    case WEST:
      printf("Moving west\n");
      // TODO(matt): Implement
      break;
    default:
      printf("Unknown move");
      break;
  }
}