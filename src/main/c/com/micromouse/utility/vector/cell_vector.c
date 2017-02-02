#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cell_vector.h"

Vector_c* make_vector_c() {
  return make_vector_c_with_size(10);
}

Vector_c* make_vector_c_with_size(int nn) {
  Vector_c* vector = malloc(sizeof(Vector_c));

  // Set the initial capacity to be nn.
  vector->capacity = nn;
  // Initially the size is 0.
  vector->size = 0;
  vector->data = malloc(sizeof(Cell*) * nn);

  // Note you do not need to allocate space for the cells
  // because they will be passed in. However you will need
  // to clean up the memory when the vector is done with
  // them.

  return vector;
}

bool vector_c_empty(Vector_c* vec) {
  assert(vec != NULL);
  return vec->size == 0;
}

int vector_c_length(Vector_c* vec) {
  assert(vec != NULL);
  return vec->size;
}

void free_vector_c(Vector_c* vec) {
  assert(vec != NULL);
  for (int ii = 0; ii < vec->size; ii++) {
    CellDestructor(vec->data[ii]);
  }
  free(vec->data);
  free(vec);
}

