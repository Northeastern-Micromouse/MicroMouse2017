#include "MazeImpl.h"
#include <math.h>

MazeImpl::MazeImpl() {
	maze_.resize(256);
  int count = 0;
  for (std::vector<Cell *>::iterator iter = maze_.begin(); iter != maze_.end(); iter++) {
    *iter = new Cell(count % 16, count / 16);
    count++;
  }
}

std::vector<Cell *> MazeImpl::GetNeighbors(int row, int col) {
	std::vector<Cell *> neighbors;
  return neighbors;
}
