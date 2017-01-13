#include "Location.h"

Location::Location(int x, int y) {
  x_ = x;
  y_ = y;
}

int Location::x() {
  return x_;
}

int Location::y() {
  return y_;
}

bool Location::isEqual(Location that) {
  return (x_ == that.x() && y_ == that.y());
}
