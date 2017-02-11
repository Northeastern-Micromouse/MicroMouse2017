#include "gtest/gtest.h"

extern "C" {
#include "src/main/c/com/micromouse/utility/vector/cell_vector.h"
}

TEST(VectorTests, AnEmptyVectorShouldBeEmpty) {
  // Given: an empty vector
  Vector_c* vec = make_vector_c();

  // Then: it should empty.
  ASSERT_TRUE(vector_c_empty(vec));

  // Clean up the memory.
  free(vec);
}

TEST(VectorTests, AnEmptyVectorShouldHaveASizeOfZero) {
  // Given: an empty vector
  Vector_c* vec = make_vector_c();

  // Then: its size should be zero
  EXPECT_EQ(0,vector_c_length(vec));

  // Clean up the memory.
  free(vec);
}
