/**
 * @file vector.h
 * @author Ghali Boucetta (gboucett@student.42.fr)
 * @brief Vector header template
 * @date 2022-09-20
 *
 */

#ifndef STC42_VECTOR_H
# define STC42_VECTOR_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdint.h>

# define CAT(a, b) CAT2(a, b)
# define CAT2(a, b) a##b

#endif // STC42_VECTOR_H

#ifndef STC42_VEC_T
# error "You must define STC42_VEC_T before including this file."
#endif

#ifndef STC42_VEC_NAME
# define STC42_VEC_NAME CAT(CAT(pq, _), STC42_PQ_T)
#endif

#ifndef STC42_VEC_PREFIX
# define STC42_VEC_PREFIX CAT(vec_, CAT(STC42_PQ_NAME, _))
#endif

#undef STC42_PQ_STRUCT_TYPE
#define STC42_PQ_STRUCT_TYPE CAT(STC42_VEC_PREFIX, t)

#ifndef STC42_VEC_LINKAGE
# define STC42_PQ_LINKAGE static inline
#endif
