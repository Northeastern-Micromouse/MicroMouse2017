#include "gtest/gtest.h"
#include "src/main/cc/maze/impl/MazeImpl.h"

namespace test {
namespace maze {
namespace impl {

using ::maze::cell::Cell;
using ::maze::impl::MazeImpl;

TEST(UtilTests, ALegalLocationShouldReturnACell) {
  // Given: a MazeImpl, an int x, and an int y
  int x = 5;
  int y = 4;
  MazeImpl _maze = MazeImpl();

  // When: requesting a particular cell
  Cell* requested = _maze(x, y);

  // Then: Cell should be from (x, y)
  EXPECT_EQ(x, requested->x());
  EXPECT_EQ(y, requested->y());
}

TEST(UtilTests, NORTHGetCellShouldReturnYIncremented) {
  // Given: A MazeImpl, an int x and an int y
  int x = 5;
  int y = 4;
  MazeImpl _maze = MazeImpl();

  // When: requesting the cell North of (x, y)
  Cell* requested = _maze(x, y + 1);

  // Then: x should be the same in Cell, y should be y + 1
  int expected_y = y + 1;
  EXPECT_EQ(x, requested->x());
  EXPECT_EQ(expected_y, requested->y());
}

}  // impl
}  // maze
}  // test
