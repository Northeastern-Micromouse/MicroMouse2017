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

 	Cell *operator()(int row, int col) {
    std::cout << "Get the cell in the maze. Row: " << row << " Column: " << col << std::endl;
 		if (row < 0 || col < 0) {
 			throw std::range_error("Index out of bounds");
 		}
 		return maze_[col + (col * row)];
 	}

	std::vector<Cell *> GetNeighbors(int row, int col);

  std::string print();

 private:
 	std::vector<Cell *> maze_;
  static constexpr int maze_size = 16;

  Cell * getCell(int row, int col, Cell::RelativeDirection direction);
	bool validMove(int row, int col, Cell::RelativeDirection direction);
};

#endif  // CC_MAZE_IMPL_MAZEIMPL_H_
