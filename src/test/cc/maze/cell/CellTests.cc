#include "gtest/gtest.h"
#include "src/main/cc/maze/cell/cell.h"

TEST(CellTests, ACellShouldBeInitializedCorrectly) {
  // Given: two cells
  Cell cell =  Cell();
  Cell cell1 = Cell(10, 10);

  // Then: they should have been initialized correctly.
  EXPECT_EQ(0, cell.x());
  EXPECT_EQ(0, cell.y());
  EXPECT_EQ(10, cell1.x());
  EXPECT_EQ(10, cell1.y());
}