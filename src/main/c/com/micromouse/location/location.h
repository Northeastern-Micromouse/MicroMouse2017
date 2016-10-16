#ifndef MICROMOUSE_LOCATION_LOCATION_H_
#define MICROMOUSE_LOCATION_LOCATION_H_

#include <stdio.h>
#include <stdlib.h>

// A struct for representing a location
// A location has a x and y position  
typedef struct Location {
    int x;
    int y;
} Location;

// Returns a pointer to a new location at the given x and y coordinates.
Location * InitializeLocation(int x, int y);

// Frees up all of the memory associated with the given location.
void LocationDestructor(Location * location);

#endif  // MICROMOUSE_LOCATION_LOCATION_H_