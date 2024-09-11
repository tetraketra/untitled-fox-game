#ifndef TTK_ATTRPACK_T
#define TTK_ATTRPACK_T

#include "toolkit.h"

/*
    === INFO ===
    1. Tools for packing nbit ints/floats ([un]signed) tightly into a GL vertex attribute.
       - All vertex attributes in GLSL are secretly int32_t[4]. If you can pack everything 
       you need into that, you save on vertex attributes.
    4. Implemented using variadic functions. 
*/

/* Special-case stack-only version of `nbitpacked_t` for use in GL rendering. */
typedef struct nbitpacked_vattr_t {
    int32_t arr[4]; /* Packed array. */
} nbitpacked_vattr_t;

#endif 