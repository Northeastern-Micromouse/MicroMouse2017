#include "gtest/gtest.h"

extern "C" {
	#include "src/main/c/com/micromouse/robot/robot.h"
}

TEST(RobotTests, ShouldInitializeARobotCorrectly) {
	// Given: a location
	Location * location = InitializeLocation(5, 5);

	// when: initializing a robot
	Robot * winslow_ = InitializeRobot(location);

	// then: the values should be set correctly.
	int count = 0;
	EXPECT_EQ(winslow_->location_->x, 5);
	EXPECT_EQ(winslow_->location_->y, 5);
	for (int row = 0; row < 16; row++) {
		for (int col = 0; col < 16; col++) {
			if (winslow_->maze_[row][col]->location->x == row) {
				if (winslow_->maze_[row][col]->location->y == col) {
					count++;
				}
			}
		}
	}
	EXPECT_EQ(256, count);

	// Free up the memory.
	RobotDestructor(winslow_);
}