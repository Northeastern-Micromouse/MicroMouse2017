#include "Location.h"

Location::Location(int x, int y) {
  x_ = x;
  y_ = y;
}

int Location::GetXLocation() {
  return x_;
}

int Location::GetYLocation() {
  return y_;
}

bool Location::isEqual(Location that) {
  return (x_ == that.GetXLocation() && y_ == that.GetYLocation());
}
