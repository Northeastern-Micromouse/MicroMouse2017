#include "robot.h"

// The maximum number of possible moves from any given cell.
int max_possible_moves = 4;

void ExploreMaze(Robot *winslow) {
	printf("Starting to explore the maze. Location is: x: %d, y: %d \n", winslow->location_->x, winslow->location_->y);

	// Start by checking the sensors.
  Move* possibleMoves = malloc(sizeof(Move) * max_possible_moves);
	PollSensors(possibleMoves, max_possible_moves);

	// Update the maze with the values.
	UpdateMaze(winslow, possibleMoves, max_possible_moves);

	// Use a Strategy to determine where to go next
	// TODO: Implement not a basic one.
  List* queue = (List*)malloc(sizeof(List));
  List** head = &queue;
  NaiveStrategy(winslow, possibleMoves, max_possible_moves, head);
  // TODO(matt): Remove this hack
  back(head);
  PrintList(queue);
  winslow->maze_[0][0]->mapped = true;

  Cell* curr = malloc(sizeof(Cell));

	while (!empty(queue)) {
		curr = Front(head);
    PrintCell(curr);
    MoveRobot(winslow, DetermineDirection(winslow, curr));
    PollSensors(possibleMoves, max_possible_moves);
    // UpdateMaze(winslow, possibleMoves, max_possible_moves);
    // NaiveStrategy(winslow, possibleMoves, max_possible_moves, head);
		// If you ever have nowhere to go or decide to go back go back.
    printf("Hello\n");
	}
	printf("Done mapping the maze.\n");

  // Clean up memory
  free(possibleMoves);
  ListDestructor(head);
}

void MoveRobot(Robot* winslow, direction_t dir) {
  switch (dir) {
    case NORTH:
      winslow->location_->y++;
      break;
    case SOUTH:
      winslow->location_->y--;
      break;
    case EAST:
      winslow->location_->x++;
      break;
    case WEST:
      winslow->location_->x--;
      break;
    case NONE:
      break;
  }
  HardwareMove(dir);
}

direction_t DetermineDirection(Robot* winslow, Cell* cell) {
  // TODO(matt): Do this better
  if (winslow->location_->x > cell->location->x) {
    return WEST;
  } else if (winslow->location_->x < cell->location->x) {
    return EAST;
  } else if (winslow->location_->y > cell->location->y) {
    return SOUTH;
  } else if (winslow->location_->y < cell->location->y) {
    return NORTH;
  }
  return NONE;
}

void UpdateMaze(Robot* winslow, Move* values, int size) {
	printf("Updating the maze\n");
  for (int i = 0; i < size; i++) {
    if (values[i].is_valid_) {
      CanMove(winslow, values[i]);
    }
  }
}

void NaiveStrategy(Robot* winslow, Move* possibleMoves, int size, List** queue) {
  printf("Naive Strategy\n");
  for (int i = 0; i < size; i++) {
    if (possibleMoves[i].is_valid_) {
      AddMove(winslow, possibleMoves[i], queue);
    }
  }
}

void AddMove(Robot* winslow, Move move, List** queue) {
  Cell* temp = InitializeCell(winslow->location_->x, winslow->location_->y);
  switch (move.dir_) {
    case NORTH:
      temp->location->y = temp->location->y + 1;
      printf("Adding move: X: %d , Y: %d\n", temp->location->x, temp->location->y);
      Append(temp, queue);
      break;
    case SOUTH:
      temp->location->y = temp->location->y - 1;
      printf("Adding move: X: %d , Y: %d\n", temp->location->x, temp->location->y);
      Append(temp, queue);
      break;
    case EAST:
      temp->location->x = temp->location->x + 1;
      printf("Adding move: X: %d , Y: %d\n", temp->location->x, temp->location->y);
      Append(temp, queue);
      break;
    case WEST:
      temp->location->x = temp->location->x - 1;
      printf("Adding move: X: %d , Y: %d\n", temp->location->x, temp->location->y);
      Append(temp, queue);
      break;
    default:
      printf("Error in AddMove. Invalid Move\n");
  }
}

void CanMove(Robot* winslow, Move move) {
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

Robot* InitializeRobot(Location* location) {
	// Create the struct for winslow.
	Robot* winslow;

	// Request memory from the heap.
	winslow = (Robot*)malloc(sizeof(Robot));

	// Check if the memory is available.
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

// Robot Location -> [Linked-list of [Moves]]
// Returns a linked list of moves for the robot to execute, starts by 
// searching the maze for the path to the goal, and returns the path as a 
// Linked-list of Moves.
Cell* SolveMaze(Robot* winslow, Location* goal) {
  // Create path to return and load starting location into path
  Location* curr_loc = winslow->location_;
  // Mark curr_loc as visited
  int curr_x = curr_loc->x;
  int curr_y = curr_loc->y;
  List* queue = InitializeList(winslow->maze_[curr_x][curr_y]);
  List** head = &queue;
  Cell* curr_cell = winslow->maze_[curr_x][curr_y];
  curr_cell->visited = true;

  while(empty(queue)) {
    curr_cell = back(head);
    curr_loc = curr_cell->location;
    int x_ = curr_loc->x;
    int y_ = curr_loc->y;
    if(x_ == goal->x && y_ == goal->y) {
      return winslow->maze_[goal->x][goal->y];
    }
    if(curr_cell->east) {
      VisitNeighbor(curr_cell, x_ + 1, y_, winslow, head);
    }
    if(curr_cell->west) {
      VisitNeighbor(curr_cell, x_ - 1, y_, winslow, head);
    }
    if(curr_cell->north) {
      VisitNeighbor(curr_cell, x_, y_ + 1, winslow, head);
    }
    if(curr_cell->south) {
      VisitNeighbor(curr_cell, x_, y_ - 1, winslow, head);
    }
  }
  return winslow->maze_[0][0]; // Did not find goal cell, return fail.
}

// Visit neighbor and update the queue
void VisitNeighbor(Cell* current_cell, int x, int y, Robot* winslow, List** head) {
  Cell* neighbor_cell = winslow->maze_[x][y];
  if(!neighbor_cell->visited) {
    neighbor_cell->visited = true;
    neighbor_cell->parent = current_cell;
    Location* neighbor_loc = neighbor_cell->location;
    Append(winslow->maze_[neighbor_loc->x][neighbor_loc->y], head);
  }
}

