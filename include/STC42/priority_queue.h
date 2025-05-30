/**
 * @file priority_queue.h
 * @author Ghali Boucetta (gboucett@student.42.fr)
 * @brief Priority queue header template
 * @date 2022-09-20
 *
 */

#define STC42_INTERNAL 42
#include "internal/template.h"

#ifndef STC42_PRIORITY_QUEUE_H
#define STC42_PRIORITY_QUEUE_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdint.h>

#endif // STC42_PRIORITY_QUEUE_H

#undef STC42_PQ_STRUCT_TYPE
#define STC42_PQ_STRUCT_TYPE STC42_MAKE_STRUCT_NAME(pq, STC42_NAME)

#ifndef STC42_PQ_LINKAGE
# define STC42_PQ_LINKAGE STC42_DEFAULT_LINKAGE
#endif

STC42_MAKE_TYPEDEF_FUN(void, pq, STC42_NAME, free, STC42_T);
STC42_MAKE_TYPEDEF_FUN(int, pq, STC42_NAME, cmp, const STC42_T, const STC42_T);

typedef struct STC42_PQ_STRUCT_TYPE
{
	STC42_T *data;
	size_t size;
	size_t capacity;

	STC42_MAKE_TYPEDEF_NAME(pq, STC42_NAME, cmp, _fun) *cmp;
	STC42_MAKE_TYPEDEF_NAME(pq, STC42_NAME, free, _fun) *free_data;
} STC42_PQ_STRUCT_TYPE;

/**
 * @brief Swap two elements in the priority queue.
 * @param a The first element.
 * @param b The second element.
 */
STC42_PQ_LINKAGE void STC42_MAKE_FUNC_NAME(pq, STC42_NAME, internal_swap)(STC42_T *a, STC42_T *b)
{
	STC42_T tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief Heapify the priority queue (i.e. make it a heap).
 * @param pq The priority queue.
 * @param i The index of the element to heapify.
 */
STC42_PQ_LINKAGE void STC42_MAKE_FUNC_NAME(pq, STC42_NAME, internal_heapify)(STC42_PQ_STRUCT_TYPE *pq, size_t i)
{
	if (pq->size <= 1)
		return;
	size_t largest = i;
	size_t left = 2 * i + 1;
	size_t right = 2 * i + 2;

	if (left < pq->size && pq->cmp(pq->data[left], pq->data[largest]) < 0)
		largest = left;
	if (right < pq->size && pq->cmp(pq->data[right], pq->data[largest]) < 0)
		largest = right;

	if (largest != i)
	{
		STC42_MAKE_FUNC_NAME(pq, STC42_NAME, internal_swap)(&pq->data[i], &pq->data[largest]);
		STC42_MAKE_FUNC_NAME(pq, STC42_NAME, internal_heapify)(pq, largest);
	}
}

/**
 * @brief Creates a new priority queue.
 * @param cmp The comparison function used in the heapify function.
 */
STC42_PQ_LINKAGE
STC42_PQ_STRUCT_TYPE *STC42_MAKE_FUNC_NAME(pq, STC42_NAME, new)(STC42_MAKE_TYPEDEF_NAME(pq, STC42_NAME, cmp, _fun) *cmp)
{
	STC42_PQ_STRUCT_TYPE *pq = (STC42_PQ_STRUCT_TYPE *)malloc(sizeof(STC42_PQ_STRUCT_TYPE));
	if (!pq)
		return NULL;
	memset(pq, 0, sizeof *pq);
	pq->cmp = cmp;
	return pq;
}

/**
 * @brief Frees the memory allocated for the priority queue.
 * @param pq The priority queue.
 */
STC42_PQ_LINKAGE void STC42_MAKE_FUNC_NAME(pq, STC42_NAME, free)(STC42_PQ_STRUCT_TYPE *pq)
{
	if (!pq)
		return;

	if (pq->free_data)
	{
		for (size_t i = 0; i < pq->size; i++)
			pq->free_data(pq->data[i]);
	}
	free(pq->data);
	free(pq);
}

/**
 * @brief Pushes an element to the priority queue.
 * @param pq The priority queue.
 * @param data The element to push.
 * @return True if the push was successful, false otherwise.
 */
STC42_PQ_LINKAGE bool STC42_MAKE_FUNC_NAME(pq, STC42_NAME, push)(STC42_PQ_STRUCT_TYPE *pq, STC42_T data)
{
	if (!pq->capacity)
	{
		pq->capacity = 128;
		pq->data = (STC42_T *)calloc(pq->capacity, sizeof(STC42_T));

		if (!pq->data)
			return false;
		pq->data[0] = data;
		pq->size = 1;
		return true;
	}
	if (pq->size == pq->capacity)
	{
		pq->capacity *= 2;
		STC42_T *tmp = (STC42_T *)realloc(pq->data, sizeof(STC42_T) * pq->capacity);
		if (!tmp)
			return false;
		pq->data = tmp;
	}
	pq->data[pq->size++] = data;
	for (long i = pq->size / 2 - 1; i >= 0; i--)
		STC42_MAKE_FUNC_NAME(pq, STC42_NAME, internal_heapify)(pq, i);
	return true;
}

/**
 * @brief Pops the top element of the priority queue.
 * @param pq The priority queue.
 * @param: ret The element popped.
 * @return True if the element was popped, false otherwise.
 */
STC42_PQ_LINKAGE bool STC42_MAKE_FUNC_NAME(pq, STC42_NAME, pop)(STC42_PQ_STRUCT_TYPE *pq, STC42_T *ret)
{
	if (!pq->size)
		return false;

	*ret = pq->data[0];
	pq->data[0] = pq->data[pq->size - 1];
	pq->size--;
	for (int64_t i = (int64_t)(pq->size / 2ul - 1ul); i >= 0; i--)
		STC42_MAKE_FUNC_NAME(pq, STC42_NAME, internal_heapify)(pq, i);
	return true;
}

// Cleanup defines to avoid name clashes and to make this header usable multiple times.

#undef STC42_PQ_PREFIX
#undef STC42_PQ_T
#undef STC42_PQ_NAME
#undef STC42_PQ_PRETTY_NAME
#undef STC42_PQ_STRUCT_TYPE
#undef STC42_PQ_LINKAGE

#include "STC42/internal/undef.h"

#undef STC42_INTERNAL
