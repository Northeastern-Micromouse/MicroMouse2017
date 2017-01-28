#ifndef MICROMOUSE_HARDWARE_HARDWARE_H_
#define MICROMOUSE_HARDWARE_HARDWARE_H_

#include <stdbool.h>
#include "src/main/c/com/micromouse/utility/direction/direction.h"

typedef struct Move {
  bool is_valid_;
  direction_t dir_;
} Move;

// Returns an array of size 4 representing the four possible moves from
// this location in the maze.
void PollSensors(Move* possibleMoves);

void HardwareMove(direction_t direction);

#endif  // MICROMOUSE_HARDWARE_HARDWARE_H_