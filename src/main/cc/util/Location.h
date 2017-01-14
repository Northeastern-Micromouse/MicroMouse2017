#ifndef CC_UTIL_LOCATION_H_
#define CC_UTIL_LOCATION_H_


#include <string>

class Location {
 public:
  Location(int x, int y);

  int x();
  int y();

  bool isEqual(Location that);

  std::string print();

 private:
  int x_;
  int y_;
};

#endif  // CC_UTIL_LOCATION_H_
