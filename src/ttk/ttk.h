#ifndef TTK_H
#define TTK_H

#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


/* Doubles `x: numeric` and returns it. Returns `1` if `x == 0`. */
#define DOUBLE_ALLOW_ZERO(x) ({ typeof(x) _x = (x); (_x == 0 ? 1 : _x*2); })

/* Returns a random float in [`0`, `RAND_MAX`]. */
#define RAND_FLOAT() ((float)rand()/(float)RAND_MAX)
/* Returns a random float in [`0`, `max`]. */
#define RAND_FLOAT_UPTO(max) (((float)rand()/(float)RAND_MAX) * max )
/* Returns a random float in [`min`, `max`]. */
#define RAND_FLOAT_BETWEEN(min, max) ({ typeof(min) _min = (min); ((float)rand()/(float)RAND_MAX) * (max - _min) + _min; })

/* Returns the max of `a: numeric` and `b: numeric`. */
#define MAX(a, b) ({ typeof(a) _a = (a); typeof(b) _b = (b); _a > _b ? _a : _b; })
/* Returns the min of `a: numeric` and `b: numeric`. */
#define MIN(a, b) ({ typeof(a) _a = (a); typeof(b) _b = (b); _a < _b ? _a : _b; })

/* Returns true if `x: numeric` is a power of two, regular code version (makes an assignment). */
#define IS_POT(x) ({ typeof(x) _x = x; (_x) && !((_x) & ((_x) - 1)); })
/* Returns true if `x: numeric` is a power of two, compiler version (no assignments). Useful in asserts. */
#define IS_POT_C(x) ( (x) && !((x) & ((x) - 1)) )

/* Clamp `x: numeric` between `min: numeric` and `max: numeric`. */
#define CLAMP(x, min, max) ({ typeof(min) _min = (min); typeof(max) _max = (max); typeof(x) _x = (x); _x < _min ? _min : _x > _max ? _max : _x; })
/* Subtract `sub: numeric` from `value: numeric`, clamped to `min: numeric`. */
#define SUB_CLAMP(x, sub, min) MAX(x - sub, min)
/* Add `add: numeric` to `value: numeric`, clamped to `max`: numeric. */
#define ADD_CLAMP(x, add, max) MIN(x + add, max)

/* Free `ptr`, then set `ptr` to `NULL`. */
#define FREE(ptr) do { ptr = (free(ptr), NULL); } while (0)

/* Print `msg: string` to stderr as log. */
#define LOG(fmt, args...) fprintf(stderr, "[LOG][%s:%d:%s]: " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ##args)
/* Print `msg: string` to stderr as debug. */
#define DEBUG(fmt, args...) fprintf(stderr, "[DBG][%s:%d:%s]: " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ##args)
/* Print `msg: string` to stderr as error. Does not exit, unlike `RUNTIME_ASSERT()`. */
#define ERROR(fmt, args...) fprintf(stderr, "[ERR][%s:%d:%s]: " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ##args)
/* Print location information to stderr as debug. */
#define WHERE fprintf(stderr, "[DBG][%s:%d:%s]\n", basename(__FILE__), __LINE__, __FUNCTION__)

/* Assert that `cond: bool_expression` is true at compile time. */
#define COMPILE_ASSERT(cond) do { (void)sizeof(char[1 - 2*!(cond)]); } while(0)
/* Assert that `cond: bool_expression` is true at runtime. */
#define RUNTIME_ASSERT(cond) do { if (!(cond)) { fprintf(stderr, "[ERR][%s:%d:%s] Assertion \"%s\" failed.\n", basename(__FILE__), __LINE__, __FUNCTION__, #cond); exit(-1); } } while(0)

/* Returns the number of elements in an array. */
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

/* Standard for loop setup with `i`. */
#define FOR_I(size) for(size_t i = 0; i<size;i++)
/* Standard for loop setup with `j`. */
#define FOR_J(size) for(size_t j = 0; j<size;j++)
/* Standard for loop setup with `k`. */
#define FOR_K(size) for(size_t k = 0; k<size;k++)

/* Standard for loop setup with `i`. */
#define FOR_X(size) for(size_t x = 0; i<size;i++)
/* Standard for loop setup with `j`. */
#define FOR_Y(size) for(size_t y = 0; j<size;j++)
/* Standard for loop setup with `k`. */
#define FOR_Z(size) for(size_t z = 0; k<size;k++)

/* Returns true if `a: float` and `b: float` are within an `epsilon: float` fraction of `a` of each other. */
#define FLOAT_EQ(a, b, epsilon) (fabs(a - b) <= epsilon * fabs(a))

/* Empty statements that have more intentionality to it. */
#define NOCODE ;
#define TODO ;
#define FIXME ;

/* Infinite loop which has more intentionality to it. */
#define FOREVER while(true)

/* More-intuitive inversion of `memcmp()`. */
#define MEM_EQ(a, b, size) (!memcmp(a, b, size))

#endif