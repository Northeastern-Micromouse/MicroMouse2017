#ifndef MICROMOUSE_CELL_VECTOR_H
#define MICROMOUSE_CELL_VECTOR_H

#include <src/main/c/com/micromouse/maze/cell.h>

typedef struct Vector_c {
  int size;
  int capacity;
  Cell** data;

  bool tight;
} Vector_c;

// Constructs a vector with an initial size of 10.
Vector_c* make_vector_c();
// Constructs a vector with an initial size.
Vector_c* make_vector_c_with_size(int);

void print_vector_c(Vector_c*);

int vector_c_length(Vector_c*);

Cell* vector_c_front(Vector_c*);

Cell* vector_c_back(Vector_c*);

bool vector_c_empty(Vector_c*);

// Takes ownership of the cell that is passed in.
// Will be responsible for cleaning up the memory.
// If a cell is passed in then nothing should free its memory
// other than this vector unless it is poped off the front
// or the back.
void append_vector_c(Vector_c*, Cell* data);

void double_size_vector_c(Vector_c*);

// Will free all of the memory associated with this vector
// including the cells it holds.
void free_vector_c(Vector_c *);

#endif  // MICROMOUSE_CELL_VECTOR_H
