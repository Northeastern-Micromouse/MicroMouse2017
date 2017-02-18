#include "gtest/gtest.h"
#include "src/main/cc/maze/cell/cell.h"

TEST(CellTests, ACellShouldBeInitializedCorrectly) {
  // Given: two cells
  maze::cell::Cell cell =  maze::cell::Cell();
  maze::cell::Cell cell1 = maze::cell::Cell(10, 10);

  // Then: they should have been initialized correctly.
  EXPECT_EQ(0, cell.x());
  EXPECT_EQ(0, cell.y());
  EXPECT_EQ(10, cell1.x());
  EXPECT_EQ(10, cell1.y());
}