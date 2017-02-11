#include "gtest/gtest.h"
#include "src/main/cc/maze/impl/MmazeImpl.h"

TEST(UtilTests, ALegalLocationShouldReturnACell) {
  // Given: a MazeImpl, an int x, and an int y
  int x = 5;
  int y = 4;
  MazeImpl _maze = MazeImpl();

  // When: requesting a particular cell
  Cell requested = _maze.getCell(x, y, None);

  // Then: Cell should be from (x, y)
  EXPECT_EQ(x, requested.x());
  EXPECT_EQ(y, requested.y());
}

TEST(UtilTests, NORTHGetCellShouldReturnYIncremented) {
  // Given: A MazeImpl, an int x and an int y
  int x = 5;
  int y = 4;
  MazeImpl _maze = MazeImpl();

  // When: requesting the cell North of (x, y)
  Cell requested = _maze.getCell(x, y, NORTH);

  // Then: x should be the same in Cell, y should be y + 1
  int expected_y = y + 1;
  EXPECT_EQ(x, requested.x());
  EXPECT_EQ(expect_y, requested.y());
}

TEST(UtilTests, RequestingAnInvalidCellLocation) {
  // Given: A MazeImpl, an int x and an int y
  int x = -2;
  int y = 7;
  MazeImpl _maze = MazeImpl();

  // When: requesting a cell from an invalid location
  Bool allowed_cell = _maze.validMove(x, y, NORTH);

  // Then: allowed_cell should be false
  EXPECT_FALSE(allowed_cell);
}

TEST(UtilTests, RequestingAValidCellLocation) {
  // Given a MazeImpl, an int x and an int y
  int x = 5
  int y = 5;
  MazeImpl _maze = MazeImpl();

  // When: requesting a cell from a valid location
  Boolean allowed_cell = _maze.validMove(x, y, NORTH);

  // Then: allowed_cell should be true
  EXPECT_TRUE(allowed_cell);
}
