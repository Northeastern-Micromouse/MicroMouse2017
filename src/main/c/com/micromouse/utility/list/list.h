#ifndef MICROMOUSE_UTILITY_LIST_LIST_H_
#define MICROMOUSE_UTILITY_LIST_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "src/main/c/com/micromouse/maze/cell.h"

// A linked list used to represent a list of cells.
typedef struct List {
	struct List* prev_;
	struct List* next_;

	// Data for the list.
	Cell* data_;
} List;

// Create a node with the given data.
List* InitializeList(Cell* data);

// Free all of the memory associated with the list. Goes through all of the 
// nodes after this node in the list and frees their memory.
void ListDestructor(List** list);

void PrintList(List* list);

// Returns the first element of the list.
Cell* Front(List** list);

// Returns the last element of the list.
Cell* back(List** list);

// Pushes the element onto the end of the list. Does not work on an empty list.
void PushBack(Cell* data, List* list);

// Appends the element to the Front of the list.
void Append(Cell* data, List** list);

// Gets the element at index in the list. Return NULL if not found.
Cell* get(int index, List* list);

// Returns if the element is in the list.
bool in(Cell* data, List* list);

// Returns the length of the list.
int length(List* list);

// Returns true if the list is empty, false otherwise.
bool empty(List* list);

// Clears the list, does not free the memory associated with the list.
void clear(List** list);

// Erases the first element to match the data in the list.
void erase(Cell* data, List** list);

// Reverses the list.
List* reverse(List** list);

// Resets the list to the head.
void resetList(List** head);

#endif  // MICROMOUSE_UTILITY_LIST_LIST_H_