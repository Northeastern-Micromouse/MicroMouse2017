#include <stdexcept>
#include <iostream>
#include "Location.h"

namespace util {
namespace location {

Location::Location(int x, int y) {
  x_ = x;
  y_ = y;
}


void Location::update(int x, int y) {
  if (x < 0 || y < 0) {
    std::cout << "Trying to update a location with a value of X: "
                 + std::to_string(x) + " Y: " + std::to_string(y) << std::endl;
  }
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

std::string Location::print() {
  // TODO(matt): Implement
  return "";
}

}
}
