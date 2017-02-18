#ifndef CC_UTIL_LOCATION_H_
#define CC_UTIL_LOCATION_H_

#include <string>

namespace util {
namespace location {

// Represents a coordinate point in a maze.
// A coordinate point has an x and a y location.
class Location {
 public:
  Location(int x, int y);

  int x();
  int y();

  // Updates the value of the location to the x and y values.
  void update(int x, int y);

  // Returns if this location is equal to that. Locations are equal if
  // both their x and y values are equal.
  bool isEqual(Location that);

  std::string print();

 private:
  int x_;
  int y_;
};

}  // location
}  // util

#endif  // CC_UTIL_LOCATION_H_
