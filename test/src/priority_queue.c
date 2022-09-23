#include <criterion/criterion.h>
#include <criterion/logging.h>

#define STC42_PQ_T int
#include "priority_queue.h"

int intcmp(int a, int b)
{
	return b - a;
}

Test(pq, new_free) {
	pq_int_t *pq = pq_int_new(intcmp);

	cr_assert(pq != NULL, "`pq` must be not NULL");
	cr_expect(pq->capacity == 0, "`pq` should have a capacity of 0");
	cr_expect(pq->data == NULL, "`pq->data` should be NULL");
	cr_expect(pq->size == 0, "`pq` should be empty");
	cr_expect(pq->free_data == NULL, "By default there should be no free function.");
	cr_expect(pq->cmp == intcmp, "Expected `intcmp` as the default comparison function.");
	pq_int_free(pq);
}

Test(pq, push_pop) {
	pq_int_t *pq = pq_int_new(intcmp);
	cr_assert(pq != NULL, "`pq` must be not NULL");

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
		cr_assert(i < sizeof expected, "More elements than expected");
		cr_log_info("Comparing %d and %d", ret, expected[i]);
		cr_expect(ret == expected[i++], "Returned integer is not expected");
	}

	pq_int_free(pq);
}