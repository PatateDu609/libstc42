#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define STC42_LST_T int
#include "STC42/list.h"

void fill_int_array(int *arr, size_t size, int min, int max)
{
	srand(time(NULL) * (getpid() ^ getuid() ^ (getppid() & getegid())));

	for (size_t i = 0; i < size; i++)
		arr[i] = (rand() % (max - min + 1)) + min;
}

Test(lst, new_free)
{
	lst_int_t *lst = lst_int_new();

	cr_assert(lst != NULL, "List allocation failed.");
	cr_expect_eq(lst->size, 0, "Size should be 0 as the list is empty.");
	cr_expect_eq(lst->start, NULL, "The list should be empty (start should be NULL).");
	cr_expect_eq(lst->end, NULL, "The list should be empty (end should be NULL).");
	cr_expect_eq(lst->destroy_data, NULL, "By default there should be no destroy function.");

	lst_int_free(lst);
	lst_int_free(NULL); // Should not crash the test...
}

Test(lst, push_back)
{
	cr_expect_not(lst_int_push_back(NULL, 21), "Push back should return false if the list is NULL.");

	lst_int_t *lst = lst_int_new();

	cr_assert(lst != NULL, "List allocation failed.");

	int data[10];
	size_t size = sizeof data / sizeof(int);
	fill_int_array(data, size, 0, 100);

	for (size_t i = 0; i < size; i++)
	{
		cr_log_info("Inserting %d...", data[i]);
		cr_expect(lst_int_push_back(lst, data[i]), "Push back should return true.");
		cr_expect_eq(lst->size, i + 1, "Wrong size...");
	}

	lst_node_int_t *node = lst->start;
	for (size_t i = 0; i < size; i++)
	{
		cr_assert(node != NULL, "Node should not be NULL");
		cr_expect(node->data == data[i], "Wrong stored data");
		node = node->next;
	}
	lst_int_free(lst);
}

Test(lst, push_front)
{
	cr_expect_not(lst_int_push_front(NULL, 21), "Push front should return false if the list is NULL.");

	lst_int_t *lst = lst_int_new();

	cr_assert(lst != NULL, "List allocation failed.");

	int data[10];
	size_t size = sizeof data / sizeof(int);
	fill_int_array(data, size, 0, 100);

	for (size_t i = 0; i < size; i++)
	{
		cr_log_info("Inserting %d...", data[i]);
		cr_expect(lst_int_push_front(lst, data[i]), "Push front should return true.");
		cr_expect_eq(lst->size, i + 1, "Wrong size...");
	}

	lst_node_int_t *node = lst->end;
	for (size_t i = 0; i < size; i++)
	{
		cr_assert(node != NULL, "Node should not be NULL");
		cr_expect(node->data == data[i], "Wrong stored data");
		node = node->prev;
	}
	lst_int_free(lst);
}

Test(lst, pop_back)
{
	lst_int_pop_back(NULL); // Should not crash...

	lst_int_t *lst = lst_int_new();

	cr_assert(lst != NULL, "List allocation failed");

	cr_expect_eq(lst_int_push_back(lst, 552), true, "Insertion should not fail...");
	cr_assert_eq(lst->size, 1, "Size should be exactly 1");
	lst_int_pop_back(lst);
	cr_expect_eq(lst->start, NULL, "After pop back lst->start should be NULL.");
	cr_expect_eq(lst->end, NULL, "After pop back lst->end should be NULL.");
	cr_expect_eq(lst->size, 0, "After pop back lst->size should be 0.");

	lst_int_push_back(lst, 120);
	lst_int_push_back(lst, 52);
	cr_assert_eq(lst->size, 2, "Size should be exactly 2");

	lst_int_pop_back(lst);
	cr_expect_eq(lst->start, lst->end, "list should have only one element");
	cr_expect_eq(lst->size, 1, "Size should be 1 as there was one pop back");

	lst_int_free(lst);
}

Test(lst, pop_front)
{
	lst_int_pop_front(NULL); // Should not crash...

	lst_int_t *lst = lst_int_new();

	cr_assert(lst != NULL, "List allocation failed");

	cr_expect_eq(lst_int_push_back(lst, 552), true, "Insertion should not fail...");
	cr_assert_eq(lst->size, 1, "Size should be exactly 1");
	lst_int_pop_front(lst);
	cr_expect_eq(lst->start, NULL, "After pop front lst->start should be NULL.");
	cr_expect_eq(lst->end, NULL, "After pop front lst->end should be NULL.");
	cr_expect_eq(lst->size, 0, "After pop front lst->size should be 0.");

	lst_int_push_back(lst, 120);
	lst_int_push_front(lst, 52);
	cr_assert_eq(lst->size, 2, "Size should be exactly 2");

	lst_int_pop_front(lst);
	cr_expect_eq(lst->start, lst->end, "list should have only one element");
	cr_expect_eq(lst->size, 1, "Size should be 1 as there was one pop front");

	lst_int_free(lst);
}