#include "gtest/gtest.h"
extern "C" {
	#include "src/main/c/com/micromouse/location/location.h"
}

TEST(LocationTests, ShouldInitializeALocationWithTheCorrectValues) {
  	// Given: and x and a y coordinate
	int x = 10;
	int y = 10;

	// When: creating a location
	Location * location = InitializeLocation(x,y);

	// Then: the values should have been initialized correctly.
	EXPECT_EQ(x, location->x);
	EXPECT_EQ(y, location->y);

	// Free up the memory.
	LocationDestructor(location);
}

TEST(LocationTests, ShouldSeeWarningWhenInitializingLocationWithTwoNegativeValues) {
  	// Given: and x and a y coordinate that are negative
	int x = -10;
	int y = -10;

	// and: capturing cout
	testing::internal::CaptureStdout();

	// When: creating a location
	Location * location = InitializeLocation(x,y);

	// Then: the values should have been initialized correctly
	EXPECT_EQ(x, location->x);
	EXPECT_EQ(y, location->y);

	// And: A warning should be printed.
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ("Initializing a location with invalid inputs. x: -10, y: -10. \n", output);

	// Free up the memory.
	LocationDestructor(location);
}

TEST(LocationTests, ShouldSeeWarningWhenInitializingLocationWithOneNegativeValues) {
  	// Given: and x and a y coordinate that are negative
	int x = -10;
	int y = 0;

	// and: capturing cout
	testing::internal::CaptureStdout();

	// When: creating a location
	Location * location = InitializeLocation(x,y);

	// Then: the values should have been initialized correctly
	EXPECT_EQ(x, location->x);
	EXPECT_EQ(y, location->y);

	// And: A warning should be printed.
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ("Initializing a location with invalid inputs. x: -10, y: 0. \n", output);

	// Free up the memory.
	LocationDestructor(location);
}

TEST(LocationTests, TheSameLocationShouldBeEqualToEachOther) {
	// Given: a location
	Location * location = InitializeLocation(5, 5);

	// then: it should be equal to itself
	EXPECT_EQ(true, SameLocation(location, location));

	// Free memory.
	LocationDestructor(location);
}

TEST(LocationTests, DifferentLocationsShouldNotBeEqual) {
	// Given: 4 different locaations
	Location * location = InitializeLocation(5, 4);
	Location * location1 = InitializeLocation(4, 5);
	Location * location2 = InitializeLocation(4, 4);
	Location * location3 = InitializeLocation(5, 5);

	// then: none of them should be equal.
	EXPECT_FALSE(SameLocation(location, location1));
	EXPECT_FALSE(SameLocation(location, location2));
	EXPECT_FALSE(SameLocation(location, location3));
	EXPECT_FALSE(SameLocation(location1, location2));
	EXPECT_FALSE(SameLocation(location1, location3));
	EXPECT_FALSE(SameLocation(location2, location3));

	// Free memory.
	LocationDestructor(location);
	LocationDestructor(location1);
	LocationDestructor(location2);
	LocationDestructor(location3);
}

TEST(LocationTests, DifferentLocationsWithTheSameValuesShouldBeEqual) {
	// Given: Two locations with the same values
	Location * location = InitializeLocation(5, 4);
	Location * location1 = InitializeLocation(5, 4);

	// Then: they should be the same
	EXPECT_NE(&location, &location1);
	EXPECT_TRUE(SameLocation(location, location1));

	// Free memory.
	LocationDestructor(location);
	LocationDestructor(location1);
}