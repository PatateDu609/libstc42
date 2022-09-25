/**
 * @file vector.h
 * @author Ghali Boucetta (gboucett@student.42.fr)
 * @brief Vector header template
 * @date 2022-09-20
 *
 */

#define STC42_INTERNAL 42
#include "internal/common.h"

#ifndef STC42_VEC_H
#define STC42_VEC_H

# include <stdlib.h>
# include <stdbool.h>

#endif

#ifndef STC42_VEC_T
#erorr "STC42_VEC_T must be defined."
#endif

#undef STC42_VEC_NAME
#ifndef STC42_VEC_PRETTY_NAME
# define STC42_VEC_NAME STC42_ADD_PREFIX(vec, STC42_VEC_T)
#else
# define STC42_VEC_NAME STC42_ADD_PREFIX(vec, STC42_VEC_PRETTY_NAME)
#endif

#undef STC42_VEC_STRUCT_TYPE
#define STC42_VEC_STRUCT_TYPE STC42_MAKE_STRUCT_NAME(STC42_VEC_NAME)

#ifndef STC42_VEC_LINKAGE
# define STC42_VEC_LINKAGE STC42_DEFAULT_LINKAGE
#endif

//STC42_MAKE_TYPEDEF_FUN(void, STC42_VEC_NAME, construct, STC42_VEC_T);
STC42_MAKE_TYPEDEF_FUN(void, STC42_VEC_NAME, destroy, STC42_VEC_T);

typedef struct STC42_VEC_STRUCT_TYPE
{
	STC42_VEC_T *data; ///< Array where the data are stored at.
	size_t size; ///< The size of the array.


	size_t capacity;

	//STC42_MAKE_TYPEDEF_NAME(STC42_VEC_NAME, construct, _fun) *construct_data;
	STC42_MAKE_TYPEDEF_NAME(STC42_VEC_NAME, destroy, _fun) *destroy_data;
} STC42_VEC_STRUCT_TYPE;

/**
 * @brief Returns a new vector instance, it will be empty at first but it can be filled up.
 *
 * @return A pointer to the new instance.
 */
STC42_VEC_LINKAGE STC42_VEC_STRUCT_TYPE *STC42_MAKE_FUNC_NAME(STC42_VEC_NAME, new)(void)
{
	STC42_VEC_STRUCT_TYPE *vec = malloc(sizeof *vec);

	if (!vec)
		return NULL;
	memset(vec, 0, sizeof *vec);
	return vec;
}

/**
 * @brief Frees a vector instance.
 *
 * @param vec The vector to be freed.
 */
STC42_VEC_LINKAGE void STC42_MAKE_FUNC_NAME(STC42_VEC_NAME, free)(STC42_VEC_STRUCT_TYPE *vec)
{
	if (!vec)
		return;
	if (vec->destroy_data)
		for (size_t i = 0; i < vec->size; i++)
			vec->destroy_data(vec->data[i]);
	free(vec->data);
	free(vec);
}

/**
 * @brief Reserves some space for a vector.
 *
 * @param vec The targeted vector.
 * @param n The wanted size (this is a multiple of `sizeof STC42_VEC_T`)
 *
 * @return Returns true if the operation succeeded, and it returns false if it fails.
 */
STC42_VEC_LINKAGE bool STC42_MAKE_FUNC_NAME(STC42_VEC_NAME, reserve)(STC42_VEC_STRUCT_TYPE *vec, size_t n)
{
	if (!vec)
		return false;
	if (vec->capacity >= n)
		return true;

	STC42_VEC_T *tmp = malloc(n * sizeof *tmp);

	if (tmp == NULL)
		return false;
	memcpy(tmp, vec->data, vec->capacity * sizeof *vec->data);
	free(vec->data);
	vec->data = tmp;
	vec->capacity = n;

	return true;
}

/**
 * @brief Pushes a new element to the vector's end. Reserves more space if necessary.
 *
 * @param vec The targeted vector.
 * @param el The element to be pushed.
 *
 * @return Returns true if the operation succeeded, and it returns false if it fails.
 */
STC42_VEC_LINKAGE bool STC42_MAKE_FUNC_NAME(STC42_VEC_NAME, push_back)(STC42_VEC_STRUCT_TYPE *vec, STC42_VEC_T el)
{
	if (!vec)
		return false;
	if (vec->capacity == 0 || vec->capacity == vec->size)
	{
		size_t cap = (vec->capacity == 0) ? 128 : vec->capacity * 2;
		if (!STC42_MAKE_FUNC_NAME(STC42_VEC_NAME, reserve)(vec, cap))
			return false;
	}
	vec->data[vec->size++] = el;
	return true;
}

/**
 * @brief Removes the last element of the vector. And it destroys it.
 *
 * @param vec The targeted vector.
 *
 * @return Returns True if the operation succeeded or false otherwise.
 */
STC42_VEC_LINKAGE bool STC42_MAKE_FUNC_NAME(STC42_VEC_NAME, pop_back)(STC42_VEC_STRUCT_TYPE *vec)
{
	if (!vec)
		return false;
	if (!vec->size)
		return false;
	if (vec->destroy_data)
		vec->destroy_data(vec->data[vec->size - 1]);
	memset(vec->data + vec->size * sizeof *vec->data, 0, sizeof *vec->data);
	vec->size--;
	return true;
}

#undef STC42_VEC_PREFIX
#undef STC42_VEC_T
#undef STC42_VEC_NAME
#undef STC42_VEC_PRETTY_NAME
#undef STC42_VEC_STRUCT_TYPE
#undef STC42_VEC_LINKAGE

#include "STC42/internal/undef.h"

#undef STC42_INTERNAL
