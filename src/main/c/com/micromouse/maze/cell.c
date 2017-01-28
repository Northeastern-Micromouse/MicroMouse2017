#include "cell.h"

bool DetermineIfOpen(Cell* cell) {
	if (cell->north && cell->east && cell->west && cell->south) {
		cell->open = true;
		return true;
	}
	cell->open = false;
	return false;
}

void PrintCell(Cell* cell) {
	if (cell == NULL) {
		printf("Cell can not be null in print cell\n");
    return;
	}
	printf("X: %d, Y: %d\n", cell->location->x, cell->location->y);
	// TODO(matt): Print more shit
}

Location* GetLocation(Cell* cell) {
	return cell->location;
}

bool SameCell(Cell* this, Cell* that) {
	if (!SameLocation(this->location, that->location)) {
		return false;
	}
	return ((this->open == that->open) &&
			(this->north == that->north) &&
			(this->south == that->south) &&
			(this->west == that->west) &&
			(this->east == that->east) &&
			(this->visited == that->visited) && 
			(this->mapped == that->mapped));
}

Cell* InitializeCell(int x, int y) {
	// Create the cell struct.
	Cell* new_cell;

	// Request memory from the heap.
	new_cell = (Cell*)malloc(sizeof(Cell));

	// Alert the user if there is no memory avaliable. 
	if (new_cell == 0) {
		printf("Error out of memory. Unable to create the cell"
			" at points x: %d, y: %d.\n", x, y);
		return NULL;
	}

	// Check for valud inputs.
	if (x < 0 || y < 0) {
		printf("Initializing a cell with invalid inputs. "
			"x: %d, y: %d. \n", x, y);
	}

	// Create all of the inner structs.
	Location* new_location = InitializeLocation(x, y);

	// Set the values.
	new_cell->location = new_location;
	new_cell->open = true;
	new_cell->north = true;
	new_cell->south = true;
	new_cell->west = true;
	new_cell->east = true;
	new_cell->visited = false;
	new_cell->mapped = false;

	return new_cell;
}

void CellDestructor(Cell* cell) {
	// Call the destructor on all of its contents.
	LocationDestructor(cell->location);
	// Free up its own memory.
	free(cell);
}