/**
 * @file undef.h
 * @author Ghali Boucetta (gboucett@student.42.fr)
 * @brief Undefine everything used by internal headers.
 * @date 2022-09-20
 *
 * @warning DISCLAIMER: This file should NOT be included outside of the scope of
 * this library.
 */

#if STC42_INTERNAL != 42
# error "You should not be including this file outside of the STC42 library."
#endif

#undef CAT
#undef CAT2
#undef STC42_ADD_PREFIX
#undef STC42_DEFAULT_LINKAGE
#undef STC42_MAKE_STRUCT_NAME
#undef STC42_MAKE_FUNC_NAME
#undef STC42_MAKE_TYPEDEF_NAME
#undef STC42_MAKE_TYPEDEF_FUN
