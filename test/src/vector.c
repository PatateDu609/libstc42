#include <signal.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#define STC42_VEC_T char *
#define STC42_VEC_PRETTY_NAME str
#include "STC42/vector.h"

void destroy_str(char *)
{
}

Test(vec, new_free)
{
	vec_str_t *vec = vec_str_new();

	cr_assert(vec != NULL, "Vector construction has failed.");
	cr_expect(vec->data == NULL, "At first, a vector should have no data.");
	cr_expect(vec->size == 0, "Size should be 0.");
	cr_expect(vec->capacity == 0, "Capacity should be 0.");

	vec_str_free(vec);
}

Test(vec, push_back)
{
	vec_str_t *vec = vec_str_new();
	cr_expect_not(vec_str_push_back(NULL, "bonjour"), "This should return false.");

	cr_assert(vec != NULL, "Vector construction has failed.");

	char *strings[] = {
		"Hello World!",
		"a",
		"b",
		"123456789",
		"987654321"
	};
	size_t size = sizeof strings / sizeof *strings;
	size_t expected_size = 0;
	for (size_t i = 0; i < size; i++)
	{
		cr_log_info("Trying to push back |%s|.", strings[i]);
		if (!vec_str_push_back(vec, strings[i]))
			cr_fatal("The push back operation failed...");
		cr_assert(vec->size == ++expected_size, "The size did not evolve...");
		cr_expect_not(strcmp(vec->data[vec->size - 1], strings[i]), "The string comparison should return no differences.");
	}
	vec_str_free(vec);
}

Test(vec, pop_back)
{
	vec_str_t *vec = vec_str_new();

	cr_assert(vec != NULL, "Vector construction has failed.");
	cr_expect_not(vec_str_pop_back(NULL), "This should return false.");

	char *strings[] = {
		"Hello World!",
		"a",
		"b",
		"123456789",
		"987654321"
	};
	size_t size = sizeof strings / sizeof *strings;

	for (size_t i = 0; i < size; i++)
		vec_str_push_back(vec, strings[i]);
	cr_expect_eq(size, vec->size, "The number of elements in the vector (%zu) is not what was expected (%zu)", vec->size, size);

	for (long i = (long)vec->size; i > 0; i--)
	{
		char *new_last = vec->size == 2 ? vec->data[vec->size - 2] : NULL; // Should be the new last
		if (!vec_str_pop_back(vec))
			cr_fatal("The pop back operation has failed.");
		cr_expect_neq((long)vec->size, i, "The new size should not be equal to the old one");
		if (i == 2)
			cr_expect_str_eq(new_last, vec->data[vec->size - 1], "The new last should be %s, not %s", new_last, vec->data[vec->size - 1]);
	}
	cr_expect_not(vec_str_pop_back(vec), "pop_back should return false");
	vec_str_free(vec);
}