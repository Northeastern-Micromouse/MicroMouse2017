#include "location.h"

Location * InitializeLocation(int x, int y) {
	// Create the location struct.
	Location * new_location;

	// Request the memory from the heap.
	new_location = (Location *)malloc(sizeof(Location));

	// Alert the user if there is no memory avaliable. 
	if (new_location == 0) {
		printf("Error out of memory. Unable to create the location\n");
		return NULL;
	}

	// Check for valid inputs.
	if (x < 0 || y < 0) {
		printf("Initializing a location with invalid inputs. "
			"x: %d, y: %d. \n", x, y);
	}

	// Set the values.
	new_location->x = x;
	new_location->y = y;
	return new_location;
}

void LocationDestructor(Location * location) {
	free(location);
}

bool SameLocation(Location * loc1, Location * loc2) {
	return ((loc1->x == loc2->x) && (loc1->y == loc2->y));
}