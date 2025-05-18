#include <gtest/gtest.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

#define STC42_TYPE int
#include "STC42/list.h"

void fill_int_array(int *arr, size_t size, int min, int max)
{
	std::srand(time(nullptr) * (getpid() ^ getuid() ^ (getppid() & getegid())));

	for (size_t i = 0; i < size; i++)
		arr[i] = (std::rand() % (max - min + 1)) + min;
}

TEST(lst, new_free)
{
	lst_int_t *lst = lst_int_new();

	ASSERT_NE(lst, nullptr) << "List allocation failed.";
	EXPECT_EQ(lst->size, 0) << "Size should be 0 as the list is empty.";
	EXPECT_EQ(lst->start, nullptr) << "The list should be empty (start should be nullptr).";
	EXPECT_EQ(lst->end, nullptr) << "The list should be empty (end should be nullptr).";
	EXPECT_EQ(lst->destroy_data, nullptr) <<  "By default there should be no destroy function.";

	lst_int_free(lst);
	lst_int_free(nullptr); // Should not crash the test...
}

TEST(lst, push_back)
{
	EXPECT_FALSE(lst_int_push_back(nullptr, 21)) << "Push back should return false if the list is nullptr.";

	lst_int_t *lst = lst_int_new();

	ASSERT_NE(lst,  nullptr) << "List allocation failed.";

	int data[10];
	size_t size = sizeof data / sizeof(int);
	fill_int_array(data, size, 0, 100);

	for (size_t i = 0; i < size; i++)
	{
		//log ("Inserting %d...", data[i]);
		EXPECT_TRUE(lst_int_push_back(lst, data[i])) << "Push back should return true.";
		EXPECT_EQ(lst->size, i + 1) << "Wrong size...";
	}

	lst_node_int_t *node = lst->start;
	for (size_t i = 0; i < size; i++)
	{
		ASSERT_NE(node, nullptr) << "Node should not be nullptr";
		EXPECT_EQ(node->data, data[i]) << "Wrong stored data";
		node = node->next;
	}
	lst_int_free(lst);
}

TEST(lst, push_front)
{
	EXPECT_FALSE(lst_int_push_front(nullptr, 21)) << "Push front should return false if the list is nullptr.";

	lst_int_t *lst = lst_int_new();

	ASSERT_NE(lst, nullptr) << "List allocation failed.";

	int data[10];
	size_t size = sizeof data / sizeof(int);
	fill_int_array(data, size, 0, 100);

	for (size_t i = 0; i < size; i++)
	{
		// LOG ("Inserting %d...", data[i]);
		EXPECT_TRUE(lst_int_push_front(lst, data[i])) << "Push front should return true.";
		EXPECT_EQ(lst->size, i + 1) << "Wrong size...";
	}

	lst_node_int_t *node = lst->end;
	for (size_t i = 0; i < size; i++)
	{
		ASSERT_NE(node, nullptr) << "Node should not be nullptr";
		EXPECT_EQ(node->data, data[i]) << "Wrong stored data";
		node = node->prev;
	}
	lst_int_free(lst);
}

TEST(lst, pop_back)
{
	lst_int_pop_back(nullptr); // Should not crash...

	lst_int_t *lst = lst_int_new();

	ASSERT_NE(lst, nullptr) << "List allocation failed";

	EXPECT_EQ(lst_int_push_back(lst, 552), true) << "Insertion should not fail...";
	ASSERT_EQ(lst->size, 1) << "Size should be exactly 1";
	lst_int_pop_back(lst);
	EXPECT_EQ(lst->start, nullptr) << "After pop back lst->start should be nullptr.";
	EXPECT_EQ(lst->end, nullptr) << "After pop back lst->end should be nullptr.";
	EXPECT_EQ(lst->size, 0) << "After pop back lst->size should be 0.";

	lst_int_push_back(lst, 120);
	lst_int_push_back(lst, 52);
	ASSERT_EQ (lst->size, 2) <<"Size should be exactly 2";

	lst_int_pop_back(lst);
	EXPECT_EQ(lst->start, lst->end) << "list should have only one element";
	EXPECT_EQ(lst->size, 1) << "Size should be 1 as there was one pop back";

	lst_int_free(lst);
}

TEST(lst, pop_front)
{
	lst_int_pop_front(nullptr); // Should not crash...

	lst_int_t *lst = lst_int_new();

	ASSERT_NE(lst, nullptr) << "List allocation failed";

	EXPECT_EQ(lst_int_push_back(lst, 552), true) << "Insertion should not fail...";
	ASSERT_EQ(lst->size, 1) << "Size should be exactly 1";
	lst_int_pop_front(lst);
	EXPECT_EQ(lst->start, nullptr) << "After pop front lst->start should be nullptr.";
	EXPECT_EQ(lst->end, nullptr) << "After pop front lst->end should be nullptr.";
	EXPECT_EQ(lst->size, 0) << "After pop front lst->size should be 0.";

	lst_int_push_back(lst, 120);
	lst_int_push_front(lst, 52);
	ASSERT_EQ(lst->size, 2) << "Size should be exactly 2";

	lst_int_pop_front(lst);
	EXPECT_EQ(lst->start, lst->end) << "list should have only one element";
	EXPECT_EQ(lst->size, 1) << "Size should be 1 as there was one pop front";

	lst_int_free(lst);
}