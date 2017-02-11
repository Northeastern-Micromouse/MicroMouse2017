#ifndef CC_MAZE_IMPL_MAZEIMPL_H_
#define CC_MAZE_IMPL_MAZEIMPL_H_

#include "maze/cell/cell.h"
#include "maze/maze.h"
#include <vector>
#include <exception>
#include <iostream>

// Class to represent a maze. A maze is a collections of Cells. 
class MazeImpl : public Maze {
 public:
 	MazeImpl();

 	Cell *operator()(int x, int y) {
    std::cout << "Get the cell in the maze. Row: " << x << " Column: " << y << std::endl;
 		if (x < 0 || y < 0) {
 			throw std::range_error("Index out of bounds");
 		}
 		return maze_[x + (maze_size * y)];
 	}

	std::vector<Cell *> GetNeighbors(int row, int col);

  std::string print();

 private:
 	std::vector<Cell *> maze_;
  static constexpr int maze_size = 16;

  Cell * getCell(int x, int y, Cell::RelativeDirection direction);
	bool validMove(int x, int y, Cell::RelativeDirection direction);
};

#endif  // CC_MAZE_IMPL_MAZEIMPL_H_
