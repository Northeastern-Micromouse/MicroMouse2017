#ifndef CC_MAZE_IMPL_MAZEIMPL_H_
#define CC_MAZE_IMPL_MAZEIMPL_H_

#include <vector>
#include <exception>
#include <iostream>
#include "../maze.h"
#include "../cell/cell.h"

namespace maze {
namespace impl {

// Class to represent a maze. A maze is a collections of Cells.
class MazeImpl : public Maze {
 public:
  MazeImpl();
  ~MazeImpl();

  maze::cell::Cell *operator()(int x, int y) {
    if (x < 0 || y < 0) {
      throw std::range_error("Index out of bounds");
    }
    return maze_[x + (maze_size * y)];
  }

  std::vector<maze::cell::Cell *> GetNeighbors(int row, int col);

  std::string print();

  void clear_maze();

 private:
  std::vector<maze::cell::Cell *> maze_;
  static constexpr int maze_size = 16;

  maze::cell::Cell * getCell(int x, int y, maze::cell::Cell::RelativeDirection direction);
  bool validMove(int x, int y, maze::cell::Cell::RelativeDirection direction);
};

}  // impl
}  // maze

#endif  // CC_MAZE_IMPL_MAZEIMPL_H_
