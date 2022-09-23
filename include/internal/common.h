/**
 * @file common.h
 * @author Ghali Boucetta (gboucett@student.42.fr)
 * @brief This contains everything useful for the lib.
 * @date 2022-09-20
 *
 * @warning DISCLAIMER: This file should NOT be included outside of the scope of
 * this library.
 */

#if STC42_INTERNAL != 42
# error "You should not be including this file outside of the STC42 library."
#endif

#define CAT(a, b) CAT2(a, b)
#define CAT2(a, b) a##b

#define STC42_ADD_PREFIX(prefix, prefixed) CAT(CAT(prefix, _), prefixed)
#define STC42_DEFAULT_LINKAGE static inline

#define STC42_MAKE_STRUCT_NAME(name) CAT(name, _t)
#define STC42_MAKE_FUNC_NAME(name, func_name) CAT(CAT(name, _), func_name)
#define STC42_MAKE_TYPEDEF_NAME(name, typedef_name, suffix) CAT(CAT(name, _), CAT(typedef_name, suffix))
#define STC42_MAKE_TYPEDEF_FUN(ret, name, typedef_name, ...) \
	typedef ret (STC42_MAKE_TYPEDEF_NAME(name, typedef_name, _fun))(__VA_ARGS__)
