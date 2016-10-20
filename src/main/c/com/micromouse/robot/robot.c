#include "robot.h"

void ExploreMaze(Robot * winslow) {
	printf("Starting to explore the maze. Location is: x: %d, y: %d \n", winslow->location_->x, winslow->location_->y);

	// Start by checking the sensors.
	SR * values = PollSensors();

	// Update the maze with the values.
	UpdateMaze(winslow, values);

	// Use a Stratgey to determine where to go next
	// TODO: Implement

	// While the maze is not mapped repeat
	while (false) {
		// TODO: Implement

		// If you ever have nowhere to go or decide to go back go back.
	}
	printf("Done mapping the maze.\n");
}

void UpdateMaze(Robot * winslow, SR * values) {
	// TODO: Implement
}

Robot * InitializeRobot(Location * location) {
	// Create the struct for winslow.
	Robot * winslow;

	// Request memory from the heap.
	winslow = (Robot *)malloc(sizeof(Robot));

	// Check if the memory is avaliable.
	if (winslow == 0) {
		printf("Error out of memory. Unable to create winslow"
		" at location x: %d, y: %d.\n", location->x, location->y);
		return NULL;
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

void RobotDestructor(Robot * winslow) {
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