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