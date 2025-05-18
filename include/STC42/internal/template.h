/**
 * @file template.h
 * @author Ghali Boucetta (gboucett@student.42.fr)
 * @date 2025-05-18
 */

#if STC42_INTERNAL != 42
# error "You should not be including this file outside of the STC42 library."
#endif

#include "common.h"

#if !defined(STC42_TYPE)
#error "Before using any STC42 header you must define the STC42 type."
#endif

#if STC42_NARGS(STC42_TYPE) >= 1
#define STC42_T STC42_GET_ARG(1, STC42_TYPE)
#endif

#if STC42_NARGS(STC42_TYPE) >= 2
#define STC42_NAME STC42_GET_ARG(2, STC42_TYPE)
#else
#define STC42_NAME STC42_T
#endif

#define STC42_MAKE_STRUCT_NAME(prefix, name) CAT(CAT(CAT(prefix, _), name), _t)
#define STC42_MAKE_FUNC_NAME(prefix, name, func_name) CAT(CAT(CAT(prefix, _), CAT(name, _)), func_name)
#define STC42_MAKE_TYPEDEF_NAME(prefix, name, typedef_name, suffix) CAT(CAT(CAT(prefix, _), CAT(name, _)), CAT(typedef_name, suffix))
#define STC42_MAKE_TYPEDEF_FUN(ret, prefix, name, typedef_name, ...) \
		typedef ret (STC42_MAKE_TYPEDEF_NAME(prefix, name, typedef_name, _fun))(__VA_ARGS__)
