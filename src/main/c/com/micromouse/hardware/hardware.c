#include <assert.h>
#include <printf.h>
#include "hardware.h"

void PollSensors(Move *arr) {
	printf("Polling the sensors\n");
  // TODO(matt): Actually do what we should do and not jsut return true for everything.
  arr[0].dir_ = NORTH;
  arr[0].is_valid_ = true;
  arr[1].dir_ = SOUTH;
  arr[1].is_valid_ = true;
  arr[2].dir_ = EAST;
  arr[2].is_valid_ = true;
  arr[3].dir_ = WEST;
  arr[3].is_valid_ = true;
}