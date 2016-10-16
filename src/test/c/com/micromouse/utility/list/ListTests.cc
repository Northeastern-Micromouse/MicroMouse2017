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

TEST(ListTests, AnEmptyListSholudHaveASizeOfZero) {
	// Given: an empty list
	List * list = NULL;

	// then: the size should be zero.
	EXPECT_EQ(0, length(list));
}

TEST(ListTests, AListOfSizeOneShouldHaveSizeOne) {
	// Given: a list of size one
	Cell * cell = InitializeCell(10, 10);
	List * list = InitializeList(cell);

	// then: the size should be one.
	EXPECT_EQ(1, length(list));

	// Free the memory.
	ListDestructor(list);
}

TEST(ListTests, AListOfSizeTwoShouldHaveSizeTwo) {
	// Given: a list of size two.
	Cell * cell_one = InitializeCell(1, 1);
	Cell * cell_two = InitializeCell(3, 3);
	List * list = InitializeList(cell_one);
	PushBack(cell_two, list);

	// then: the size should be two.
	EXPECT_EQ(2, length(list));

	// Free the memory.
	ListDestructor(list);
}

TEST(ListTests, ShouldRecieveWarningWhenPushingBackToAnEmptyList) {
	// Given: an empty list and some data
	List * list = NULL;
	Cell * cell_one = InitializeCell(1, 1);

	// and: capturing cout
	testing::internal::CaptureStdout();

	// when: trying to PushBack to the empty list
	PushBack(cell_one, list);

	std::string output = testing::internal::GetCapturedStdout();

	// then: a warning should be seen
	EXPECT_EQ("Cannot PushBack onto an empty List. \n", output);
	
	// and: the list should be NULL
	EXPECT_EQ(NULL, list);

	// Free the memory.
	CellDestructor(cell_one);
}

TEST(ListTests, ChangingACellChangesItsValueInTheList) {
	// Given: a list of size two.
	Cell * cell_one = InitializeCell(1, 1);
	Cell * cell_two = InitializeCell(3, 3);
	List * list = InitializeList(cell_one);
	PushBack(cell_two, list);

	// then: the size should be two.
	ASSERT_EQ(2, length(list));

	// and: the data in the second element should be correct
	EXPECT_EQ(3, list->next_->data_->location->x);
	EXPECT_EQ(3, list->next_->data_->location->y);

	// when: changing the data for a cell
	cell_two->location->x = 10;
	cell_two->location->y = 10;

	// then: the values in the list should be updated.
	EXPECT_EQ(10, list->next_->data_->location->x);
	EXPECT_EQ(10, list->next_->data_->location->y);

	// Free the memory.
	ListDestructor(list);
}

TEST(ListTests, AppendingToAnEmptyListShouldHaveAListOfSizeOne) {
	// Given: an empty list and some data
	List * list = NULL;
	Cell * data = InitializeCell(10, 10);

	// when: appending to the list
	List ** list_head = (List **)malloc(sizeof(List *));
	list_head = &list;
	Append(data, list_head);

	// then: the size should be one and the data should be correct.
	ASSERT_EQ(1, length(list));
	EXPECT_EQ(10, list->data_->location->x);
	EXPECT_EQ(10, list->data_->location->y);

	// and: It should be at the head.
	EXPECT_EQ(NULL, list->prev_);

	// Free the memory
	ListDestructor(list);
}

TEST(ListTests, AppendingToAListShouldPlaceItAtItsHead) {
	// Given: A list and some data
	Cell * cell_one = InitializeCell(1, 1);
	Cell * cell_two = InitializeCell(3, 3);
	Cell * cell_three = InitializeCell(5, 5);
	List * list = InitializeList(cell_one);
	PushBack(cell_two, list);

	// when: appending to the list
	List ** list_head = (List **)malloc(sizeof(List *));
	list_head = &list;
	Append(cell_three, list_head);

	// then: the size should be one and the data should be correct.
	ASSERT_EQ(3, length(list));

	// and: It should be at the head
	EXPECT_EQ(NULL, list->prev_);

	// and: the data should be correct.
	EXPECT_EQ(5, list->data_->location->x);
	EXPECT_EQ(5, list->data_->location->y);

	// Free the memory
	ListDestructor(list);
}

TEST(ListTests, AppendingToAListOfSizeOneShouldWork) {
	// Given: A list and some data
	Cell * cell_one = InitializeCell(1, 1);
	Cell * cell_two = InitializeCell(3, 3);
	List * list = InitializeList(cell_one);

	// when: appending to the list
	List ** list_head = (List **)malloc(sizeof(List *));
	list_head = &list;
	Append(cell_two, list_head);

	// then: the size should be one and the data should be correct.
	ASSERT_EQ(2, length(list));

	// and: It should be at the head
	EXPECT_EQ(NULL, list->prev_);

	// and: the data should be correct.
	EXPECT_EQ(3, list->data_->location->x);
	EXPECT_EQ(3, list->data_->location->y);

	// Free the memory
	ListDestructor(list);	
}

TEST(ListTests, PushingBackToAListOfSizeOneShouldWorkCorrectly) {
	// Given: a list of size one and some data.
	Cell * cell_one = InitializeCell(1, 1);
	Cell * cell_two = InitializeCell(3, 3);
	List * list = InitializeList(cell_one);

	// when: pushing back to the list
	PushBack(cell_two, list);

	// then: the size should be correct
	ASSERT_EQ(2, length(list));

	// and: the data should be correct
	EXPECT_EQ(1, list->data_->location->x);
	EXPECT_EQ(1, list->data_->location->y);
	EXPECT_EQ(3, list->next_->data_->location->x);
	EXPECT_EQ(3, list->next_->data_->location->y);

	// and: the links should be correct.
	EXPECT_EQ(1, list->next_->prev_->data_->location->x);
	EXPECT_EQ(1, list->next_->prev_->data_->location->y);

	// Free the memory.
	ListDestructor(list);
}

TEST(ListTests, PushingBackToAListOfSizeTwoShouldWorkCorrectly) {
	// Given: a list of size one and some data.
	Cell * cell_one = InitializeCell(1, 1);
	Cell * cell_two = InitializeCell(3, 3);
	Cell * cell_three = InitializeCell(5, 5);
	List * list = InitializeList(cell_one);
	PushBack(cell_two, list);

	// when: pushing back to the list
	PushBack(cell_three, list);

	// then: the size should be correct
	ASSERT_EQ(3, length(list));

	// and: the data should be correct
	EXPECT_EQ(1, list->data_->location->x);
	EXPECT_EQ(1, list->data_->location->y);
	list = list->next_;
	EXPECT_EQ(3, list->data_->location->x);
	EXPECT_EQ(3, list->data_->location->y);
	EXPECT_EQ(5, list->next_->data_->location->x);
	EXPECT_EQ(5, list->next_->data_->location->y);

	// and: the links should be correct.
	EXPECT_EQ(3, list->next_->prev_->data_->location->x);
	EXPECT_EQ(3, list->next_->prev_->data_->location->y);

	// Free the memory.
	ListDestructor(list);
}
