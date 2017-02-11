#include "gtest/gtest.h"
#include "src/main/cc/util/Location.h"

TEST(UtilTests, ALocationShouldHaveTheCorrectXAndYValues) {
  // Given: and x and a y coordinate.
  int x = 10;
  int y = 5;

  // When: creating a location.
  Location location = Location(x, y);

  // Then: the x and y values should be set correctly.
  EXPECT_EQ(10, location.x());
  EXPECT_EQ(5, location.y());
}

TEST(UtilTests, ALocationShouldHaveTheCorrectValuesWhenUpdated) {
  // Given: and x and a y coordinate.
  int x = 10;
  int y = 5;

  // When: creating a location.
  Location location = Location(x, y);

  // and: updating the values of the location
  location.update(20, 30);

  // Then: the values of the locations should be updated
  EXPECT_EQ(20, location.x());
  EXPECT_EQ(30, location.y());
}

TEST(UtilTests, TheSameLocationShouldBeEqualToItself) {
  // Given: a location
  Location location = Location(2, -1);


  // Then: it should be equal to itself.
  EXPECT_TRUE(location.isEqual(location));
}

TEST(UtilTests, TwoLocationsWithTheSameValueShouldBeEqual) {
  // Given: a two locations with the same value
  Location location = Location(2, -1);
  Location location1 = Location(2, -1);


  // Then: they should be equal to each other.
  EXPECT_TRUE(location.isEqual(location1));
}

TEST(UtilTests, TwoLocationsWithDifferentValuesShouldNotBeEqual) {
  // Given: a two locations with the same value
  Location location = Location(2, -1);
  Location location1 = Location(2, 0);


  // Then: they should not be equal to each other.
  EXPECT_FALSE(location.isEqual(location1));
}

