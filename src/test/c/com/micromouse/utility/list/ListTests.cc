#include "gtest/gtest.h"

extern "C" {
	#include "src/main/c/com/micromouse/utility/list/list.h"
}

TEST(ListTests, ShouldInitializeANodeCorreectly) {
	// Given: a cell containing data.
	Cell * cell = InitializeCell(10, 10);

	// When: initializing a list
	List * list = InitializeList(cell);

	// Then: the data should be initialized correctly.
	EXPECT_EQ(10, list->data_->location->x);
	EXPECT_EQ(10, list->data_->location->y);
	EXPECT_EQ(true, list->data_->top);
	EXPECT_EQ(true, list->data_->bottom);
	EXPECT_EQ(true, list->data_->left);
	EXPECT_EQ(true, list->data_->right);
	EXPECT_EQ(false, list->data_->mapped);
	EXPECT_EQ(false, list->data_->visited);
	EXPECT_EQ(true, list->data_->open);

	// Free the memory.
	ListDestructor(list);
}
