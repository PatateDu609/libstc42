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

#define STC42_NARGS(...) STC42_NARGS_(__VA_ARGS__, STC42_RSEQ())
#define STC42_NARGS_(...) STC42_NARGS2_(__VA_ARGS__)
#define STC42_NARGS2_( \
	_1, _2, _3, _4, _5, _6, _7, _8, _9, \
	_10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
	_20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
	_30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
	_40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
	_50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
	_60, _61, _62, _63, N, ...) N

#define STC42_RSEQ() \
						  63,62,61,60, \
		59,58,57,56,55,54,53,52,51,50, \
		49,48,47,46,45,44,43,42,41,40, \
		39,38,37,36,35,34,33,32,31,30, \
		29,28,27,26,25,24,23,22,21,20, \
		19,18,17,16,15,14,13,12,11,10, \
		9,8,7,6,5,4,3,2,1,0,

#define STC42_EXPAND(...) __VA_ARGS__
#define STC42_GET_ARG(N, ...) STC42_EXPAND(STC42_GET_ARG##N(__VA_ARGS__,))
#define STC42_GET_ARG1(a, ...) a
#define STC42_GET_ARG2(a, b, ...) b
#define STC42_GET_ARG3(a, b, c, ...) c
#define STC42_GET_ARG4(a, b, c, d, ...) d

#define CAT(a, b) CAT2(a, b)
#define CAT2(a, b) a##b

#define STC42_ADD_PREFIX(prefix, prefixed) CAT(CAT(prefix, _), prefixed)
#define STC42_DEFAULT_LINKAGE static inline