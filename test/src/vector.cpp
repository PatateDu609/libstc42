#include <gtest/gtest.h>
#include <malloc.h>

#define STC42_TYPE const char *,str
#include "STC42/vector.h"

TEST(vec, new_free)
{
	vec_str_t* vec = vec_str_new();

	ASSERT_NE(vec, nullptr) << "Vector construction has failed.";
	EXPECT_EQ(vec->data, nullptr) << "At first, a vector should have no data.";
	EXPECT_EQ(vec->size, 0) << "Size should be 0.";
	EXPECT_EQ(vec->capacity, 0) << "Capacity should be 0.";

	vec_str_free(vec);
}

TEST(vec, push_back)
{
	vec_str_t* vec = vec_str_new();
	EXPECT_FALSE(vec_str_push_back(NULL, "bonjour")) << "This should return false.";

	ASSERT_NE(vec, nullptr) << "Vector construction has failed.";

	const char* strings[] = {
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
		ASSERT_TRUE(vec_str_push_back(vec, strings[i])) << "The push back operation failed...";
		EXPECT_EQ(vec->size, ++expected_size) << "The size did not evolve...";
		EXPECT_STREQ(vec->data[vec->size - 1], strings[i]) << "The string comparison should return no differences.";
	}
	vec_str_free(vec);
}

TEST(vec, pop_back)
{
	vec_str_t* vec = vec_str_new();

	ASSERT_NE(vec, nullptr) << "Vector construction has failed.";
	EXPECT_FALSE(vec_str_pop_back(NULL));

	const char* strings[] = {
		"Hello World!",
		"a",
		"b",
		"123456789",
		"987654321"
	};
	size_t size = sizeof strings / sizeof *strings;

	for (size_t i = 0; i < size; i++)
		vec_str_push_back(vec, strings[i]);
	EXPECT_EQ(size, vec->size);

	for (long i = (long)vec->size; i > 0; i--)
	{
		const char* new_last = vec->size == 2 ? vec->data[vec->size - 2] : NULL; // Should be the new last
		ASSERT_TRUE(vec_str_pop_back(vec));
		EXPECT_NE(vec->size, i);
	}
	EXPECT_FALSE(vec_str_pop_back(vec));
	vec_str_free(vec);
}

TEST(vec, reserve)
{
	vec_str_t* vec = vec_str_new();

	ASSERT_NE(vec, nullptr) << "Vector construction has failed.";
	EXPECT_FALSE(vec_str_reserve(nullptr, 54));

	EXPECT_TRUE(vec_str_reserve(vec, 12));
	EXPECT_EQ(vec->capacity, 12) << "The announced capacity should be 12.";
	EXPECT_GT(malloc_usable_size(vec->data), 12) << "We should have a usable size greater than 12.";

	vec_str_free(vec);
}
