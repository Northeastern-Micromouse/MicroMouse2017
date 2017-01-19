#include "robot.h"

// The maximum number of possible moves from any given cell.
int max_possible_moves = 4;

void ExploreMaze(Robot *winslow) {
	printf("Starting to explore the maze. Location is: x: %d, y: %d \n", winslow->location_->x, winslow->location_->y);

	// Start by checking the sensors.
  Move *possibleMoves = malloc(sizeof(Move) * max_possible_moves);
	PollSensors(possibleMoves);

	// Update the maze with the values.
	UpdateMaze(winslow, possibleMoves, max_possible_moves);

	// Use a Strategy to determine where to go next
	// TODO: Implement not a basic one.
  List *queue = (List *)malloc(sizeof(List));
  List **head = &queue;
  NaiveStrategy(winslow, possibleMoves, max_possible_moves, head);
  winslow->maze_[0][0]->mapped = true;


	// While the maze is not mapped repeat
	while (!empty(queue)) {
		// TODO: Implement

		// If you ever have nowhere to go or decide to go back go back.
	}
	printf("Done mapping the maze.\n");

  // Clean up memory
  free(possibleMoves);
}

void UpdateMaze(Robot *winslow, Move *values, int size) {
	printf("Updating the maze\n");
  for (int i = 0; i < size; i++) {
    if (values[i].is_valid_) {
      CanMove(winslow, values[i]);
    }
  }
}

void NaiveStrategy(Robot *winslow, Move *possibleMoves, int size, List **queue) {
  printf("Naive Strategy\n");
  for (int i = 0; i < size; i++) {
    if (possibleMoves[i].is_valid_) {
      // AddMove(winslow, possibleMoves[i], queue);
    }
  }
}

void CanMove(Robot *winslow, Move move) {
  switch (move.dir_) {
    case NORTH:
      winslow->maze_[winslow->location_->x][winslow->location_->y]->north = true;
      break;
    case SOUTH:
      winslow->maze_[winslow->location_->x][winslow->location_->y]->south = true;
      break;
    case EAST:
      winslow->maze_[winslow->location_->x][winslow->location_->y]->east = true;
      break;
    case WEST:
      winslow->maze_[winslow->location_->x][winslow->location_->y]->west = true;
      break;
    default:
      printf("Error in CanMove. Invalid Move\n");
  }
}

Robot* InitializeRobot(Location * location) {
	// Create the struct for winslow.
	Robot* winslow;

	// Request memory from the heap.
	winslow = (Robot*)malloc(sizeof(Robot));

	// Check if the memory is avaliable.
	if (winslow == 0) {
		printf("Error out of memory. Unable to create winslow"
		" at location x: %d, y: %d.\n", location->x, location->y);
		return NULL;
	}

	// Check that the location is a valid location.
	if (location->x < 0 || location->y < 0) {
		printf("Invalid inputs when creating winslow. "
			"The location is: x: %d, y: %d. \n", location->x, location->y);
	}

	// Set the values.
	winslow->location_ = location;
	for (int row = 0; row < 16; row++) {
		for (int col = 0; col < 16; col++) {
			winslow->maze_[row][col] = InitializeCell(row, col);
		}
	}
	return winslow;
}

void RobotDestructor(Robot* winslow) {
	// Call the destructor on all of its contents.
	LocationDestructor(winslow->location_);
	for (int row = 0; row < 16; row++) {
		for (int col = 0; col < 16; col++) {
			CellDestructor(winslow->maze_[row][col]);
		}
	}

	// Free up the memory for the Robot
	free(winslow);
}