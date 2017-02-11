#include "gtest/gtest.h"
extern "C" {
	#include "src/main/c/com/micromouse/maze/cell.h"
}

TEST(CellTests, ShouldInitialzeACellCorrectly) {
	// Given: x and y coordiates
	int x = 10;
	int y = 5;

	// when: initializing the cell
	Cell * cell = InitializeCell(x, y);

	// then: the cell should be initialized correctly.
	EXPECT_EQ(x, cell->location->x);
	EXPECT_EQ(y, cell->location->y);
	EXPECT_EQ(true, cell->top);
	EXPECT_EQ(true, cell->bottom);
	EXPECT_EQ(true, cell->left);
	EXPECT_EQ(true, cell->right);
	EXPECT_EQ(true, cell->open);
	EXPECT_EQ(false, cell->mapped);
	EXPECT_EQ(false, cell->visited);

	// Free up the memory.
	CellDestructor(cell);
}

TEST(CellTests, ShouldSeeWarningIfInitializedWithTwoNegativeValues) {
	// Given: x and y coordiates
	int x = -10;
	int y = -5;

	// and: capturing cout
	testing::internal::CaptureStdout();

	// when: initializing the cell
	Cell * cell = InitializeCell(x, y);

	// then: the cell should be initialized correctly.
	EXPECT_EQ(x, cell->location->x);
	EXPECT_EQ(y, cell->location->y);
	EXPECT_EQ(true, cell->top);
	EXPECT_EQ(true, cell->bottom);
	EXPECT_EQ(true, cell->left);
	EXPECT_EQ(true, cell->right);
	EXPECT_EQ(true, cell->open);
	EXPECT_EQ(false, cell->mapped);
	EXPECT_EQ(false, cell->visited);

	// And: A warning should be printed.
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "Initializing a cell with invalid inputs. x: -10, y: -5. \n";
	expected += "Initializing a location with invalid inputs. x: -10, y: -5. \n";
	EXPECT_EQ(expected, output);

	// Free up the memory.
	CellDestructor(cell);
}

TEST(CellTests, ShouldSeeWarningIfInitializedWithNegativeX) {
	// Given: x and y coordiates
	int x = -10;
	int y = 20;

	// and: capturing cout
	testing::internal::CaptureStdout();

	// when: initializing the cell
	Cell * cell = InitializeCell(x, y);

	// then: the cell should be initialized correctly.
	EXPECT_EQ(x, cell->location->x);
	EXPECT_EQ(y, cell->location->y);
	EXPECT_EQ(true, cell->top);
	EXPECT_EQ(true, cell->bottom);
	EXPECT_EQ(true, cell->left);
	EXPECT_EQ(true, cell->right);
	EXPECT_EQ(true, cell->open);
	EXPECT_EQ(false, cell->mapped);
	EXPECT_EQ(false, cell->visited);

	// And: A warning should be printed.
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "Initializing a cell with invalid inputs. x: -10, y: 20. \n";
	expected += "Initializing a location with invalid inputs. x: -10, y: 20. \n";
	EXPECT_EQ(expected, output);

	// Free up the memory.
	CellDestructor(cell);
}

TEST(CellTests, ShouldSeeWarningIfInitializedWithNegativeY) {
	// Given: x and y coordiates
	int x = 0;
	int y = -8;

	// and: capturing cout
	testing::internal::CaptureStdout();

	// when: initializing the cell
	Cell * cell = InitializeCell(x, y);

	// then: the cell should be initialized correctly.
	EXPECT_EQ(x, cell->location->x);
	EXPECT_EQ(y, cell->location->y);
	EXPECT_EQ(true, cell->top);
	EXPECT_EQ(true, cell->bottom);
	EXPECT_EQ(true, cell->left);
	EXPECT_EQ(true, cell->right);
	EXPECT_EQ(true, cell->open);
	EXPECT_EQ(false, cell->mapped);
	EXPECT_EQ(false, cell->visited);

	// And: A warning should be printed.
	std::string output = testing::internal::GetCapturedStdout();
	std::string expected = "Initializing a cell with invalid inputs. x: 0, y: -8. \n";
	expected += "Initializing a location with invalid inputs. x: 0, y: -8. \n";
	EXPECT_EQ(expected, output);

	// Free up the memory.
	CellDestructor(cell);
}

TEST(CellTests, SameCellsShouldBeEqual) {
	// Given: A cell
	Cell * cell = InitializeCell(5, 5);

	// Then: it should be equal to itself
	EXPECT_TRUE(SameCell(cell, cell));

	// Free up memory
	CellDestructor(cell);
}

TEST(CellTests, DifferentCellsShouldntBeEqual) {
	// Given: two different cells
	Cell * cell = InitializeCell(5, 5);
	Cell * cell1 = InitializeCell(5, 6);

	// Then: they should not be equal
	EXPECT_FALSE(SameCell(cell, cell1));

	// Free up memory
	CellDestructor(cell);
	CellDestructor(cell1);
}

TEST(CellTests, CellsWithTheSameValueShouldBeEqual) {
		// Given: two different cells with the same values
	Cell * cell = InitializeCell(5, 5);
	Cell * cell1 = InitializeCell(5, 5);

	// Then: they should be equal
	EXPECT_TRUE(SameCell(cell, cell1));

	// Free up memory
	CellDestructor(cell);
	CellDestructor(cell1);
}