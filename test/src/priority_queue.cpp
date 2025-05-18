#include <gtest/gtest.h>

#define STC42_TYPE int
#include "STC42/priority_queue.h"

int intcmp(int a, int b)
{
	return b - a;
}

TEST(pq, new_free) {
	pq_int_t *pq = pq_int_new(intcmp);

	ASSERT_NE(pq, nullptr) << "`pq` must be not NULL";
	EXPECT_EQ(pq->capacity, 0) << "`pq` should have a capacity of 0";
	EXPECT_EQ(pq->data, nullptr) << "`pq->data` should be NULL";
	EXPECT_EQ(pq->size, 0) << "`pq` should be empty";
	EXPECT_EQ(pq->free_data,  nullptr) << "By default there should be no free function.";
	EXPECT_EQ(pq->cmp, intcmp) << "Expected `intcmp` as the default comparison function.";
	pq_int_free(pq);
}

TEST(pq, push_pop) {
	pq_int_t *pq = pq_int_new(intcmp);
	ASSERT_NE(pq, nullptr) << "`pq` must be not NULL";

	pq_int_push(pq, 73);
	pq_int_push(pq, 61);
	pq_int_push(pq, 92);
	pq_int_push(pq, 22);
	pq_int_push(pq, 55);
	pq_int_push(pq, 42);
	pq_int_push(pq, 43);
	pq_int_push(pq, 50);

	int expected[] = { 92, 73, 61, 55, 50, 43, 42, 22 };
	int ret;
	size_t i = 0;
	while (pq_int_pop(pq, &ret))
	{
		ASSERT_LT(i, sizeof expected) << "More elements than expected";
		EXPECT_EQ(ret, expected[i++]) << "Returned integer is not expected";
	}

	pq_int_free(pq);
}