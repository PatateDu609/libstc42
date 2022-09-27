/**
 * @file list.h
 * @author Ghali Boucetta (gboucett@student.42.fr)
 * @date 2022-09-26
 */

#define STC42_INTERNAL 42

#include "internal/common.h"

#ifndef STC42_LIST_H
#define STC42_LIST_H

# include <stdlib.h>
# include <stdbool.h>

#endif // STC42_LIST_H

#ifndef STC42_LST_T
# error "The STC42_LST_T should be defined before including this file."
#endif

#undef STC42_LST_NAME
#ifndef STC42_LST_PRETTY_NAME
# define STC42_LST_NAME STC42_ADD_PREFIX(lst, STC42_LST_T)
#else
# define STC42_LST_NAME STC42_ADD_PREFIX(lst, STC42_LST_PRETTY_NAME)
#endif

#undef STC42_LST_STRUCT_TYPE
#define STC42_LST_STRUCT_TYPE STC42_MAKE_STRUCT_NAME(STC42_LST_NAME)
#undef STC42_LST_NODE_TYPE
#define STC42_LST_NODE_TYPE STC42_MAKE_STRUCT_NAME(STC42_ADD_PREFIX(lst_node, STC42_LST_T))

#ifndef STC42_LST_LINKAGE
# define STC42_LST_LINKAGE STC42_DEFAULT_LINKAGE
#endif

STC42_MAKE_TYPEDEF_FUN(void, STC42_LST_NAME, destroy, STC42_LST_T);

typedef struct STC42_LST_NODE_TYPE
{
	struct STC42_LST_NODE_TYPE *next;
	struct STC42_LST_NODE_TYPE *prev;
	STC42_LST_T data;
} STC42_LST_NODE_TYPE;

typedef struct STC42_LST_STRUCT_TYPE
{
	STC42_LST_NODE_TYPE *start;
	STC42_LST_NODE_TYPE *end;
	size_t size;

	STC42_MAKE_TYPEDEF_NAME(STC42_LST_NAME, destroy, _fun) *destroy_data;
} STC42_LST_STRUCT_TYPE;

/**
 * @brief Makes a new instance of list.
 *
 * @return A pointer to the new instance.
 */
STC42_LST_LINKAGE STC42_LST_STRUCT_TYPE *STC42_MAKE_FUNC_NAME(STC42_LST_NAME, new)(void)
{
	STC42_LST_STRUCT_TYPE *lst = malloc(sizeof *lst);

	if (!lst)
		return NULL;
	memset(lst, 0, sizeof *lst);
	return lst;
}

/**
 * @brief Frees a list instance and destroy every node and data in it.
 *
 * @param lst The list to be freed.
 */
STC42_LST_LINKAGE void STC42_MAKE_FUNC_NAME(STC42_LST_NAME, free)(STC42_LST_STRUCT_TYPE *lst)
{
	if (!lst)
		return ;

	STC42_LST_NODE_TYPE *node = lst->start;

	while (node)
	{
		STC42_LST_NODE_TYPE *tmp = node->next;
		if (lst->destroy_data)
			lst->destroy_data(node->data);
		free(node);
		node = tmp;
	}
	free(lst);
}

/**
 * @brief Inserts a new element at the end of the list.
 *
 * @param lst The list for which we want the operation to be applied to.
 * @param data The data to be inserted.
 *
 * @return True if the operation succeeded, false otherwise.
 */
STC42_LST_LINKAGE bool STC42_MAKE_FUNC_NAME(STC42_LST_NAME, push_back)(STC42_LST_STRUCT_TYPE *lst, STC42_LST_T data)
{
	if (!lst)
		return false;
	STC42_LST_NODE_TYPE *node = malloc(sizeof *node);

	if (!node)
		return false;
	node->data = data;
	node->next = node->prev = NULL;

	lst->size++;
	if (lst->size == 1)
	{
		lst->start = lst->end = node;
		return true;
	}
	lst->end->next = node;
	node->prev = lst->end;
	lst->end = node;
	return true;
}

/**
 * @brief Removes the last element of the list.
 *
 * @param lst The targeted list.
 */
STC42_LST_LINKAGE void STC42_MAKE_FUNC_NAME(STC42_LST_NAME, pop_back)(STC42_LST_STRUCT_TYPE *lst)
{
	if (!lst)
		return ;
	STC42_LST_NODE_TYPE *new_last = lst->end->prev;

	if (lst->destroy_data)
		lst->destroy_data(lst->end->data);
	free(lst->end);
	if (lst->size == 1)
	{
		lst->size--;
		lst->end = lst->start = NULL;
		return;
	}

	new_last->next = NULL;
	lst->end = new_last;
	lst->size--;
	if (lst->size == 1)
		lst->start = lst->end;
}

/**
 * @brief Add a new element to the beginning of the list.
 *
 * @param lst The list.
 * @param data The new element.
 *
 * @return Returns true or false depending on the success or the failure of the operation.
 */
STC42_LST_LINKAGE bool STC42_MAKE_FUNC_NAME(STC42_LST_NAME, push_front)(STC42_LST_STRUCT_TYPE *lst, STC42_LST_T data)
{
	if (!lst)
		return false;
	STC42_LST_NODE_TYPE *node = malloc(sizeof *node);

	if (!node)
		return false;
	node->data = data;
	node->prev = node->next = NULL;

	lst->size++;
	if (lst->size == 1)
	{
		lst->start = lst->end = node;
		return true;
	}

	node->next = lst->start;
	lst->start->prev = node;
	lst->start = node;
	return true;
}

/**
 * @brief Removes the first element of the list.
 *
 * @param lst The list.
 */
STC42_LST_LINKAGE void STC42_MAKE_FUNC_NAME(STC42_LST_NAME, pop_front)(STC42_LST_STRUCT_TYPE *lst)
{
	if (!lst)
		return;
	STC42_LST_NODE_TYPE *new_start = lst->start->next;

	if (lst->destroy_data)
		lst->destroy_data(lst->start->data);
	free(lst->start);
	if (lst->size == 1)
	{
		lst->start = lst->end = NULL;
		lst->size--;
		return;
	}

	new_start->prev = NULL;
	lst->start = new_start;
	lst->size--;
	if (lst->size == 1)
		lst->end = lst->start;
}

#undef STC42_LST_T
#undef STC42_LST_NAME
#undef STC42_LST_PRETTY_NAME
#undef STC42_LST_STRUCT_TYPE
#undef STC42_LST_NODE_TYPE
#undef STC42_LST_LINKAGE

#include "STC42/internal/undef.h"

#undef STC42_INTERNAL
