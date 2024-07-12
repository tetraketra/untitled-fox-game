#ifndef TTK_H
#define TTK_H

#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <assert.h>

/*
    === INFO ===
    1. Tetra's Toolkit, "ttk", is a series of macros and utilities built by @TetraKetra.
    2. This file contains macros for use in all ttk sublibraries, plus wherever else you want.
*/

/* Suppress unused variable warnings. */
#define IGNORE(x) ((void)(x))

/* Does nothing. Communicates "this should be empty". */
#define NOCODE ;
/* Does nothing. Communicates "this will eventually have something". */
#define TODO ;
/* Does nothing. Communicates "this needs to have something". */
#define FIXME ;

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

/* Clamp `x: numeric` between `min: numeric` and `max: numeric`. */
#define CLAMP(x, min, max) ({ typeof(min) _min = (min); typeof(max) _max = (max); typeof(x) _x = (x); _x < _min ? _min : _x > _max ? _max : _x; })
/* Subtract `sub: numeric` from `value: numeric`, clamped to `min: numeric`. */
#define SUB_CLAMP(x, sub, min) MAX(x - sub, min)
/* Add `add: numeric` to `value: numeric`, clamped to `max`: numeric. */
#define ADD_CLAMP(x, add, max) MIN(x + add, max)

/* Free `ptr`, then set `ptr` to `NULL`. */
#define FREE(ptr) do { ptr = (free(ptr), NULL); } while (0)

/* Print location information to stderr as debug. */
#define WHERE fprintf(stderr, "[DBG][%s:%d:%s]\n", basename(__FILE__), __LINE__, __FUNCTION__)
/* Print `msg: string` to stderr as log. */
#define LOG(fmt, args...) fprintf(stderr, "[LOG][%s:%d:%s]: " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ##args)
/* Print `msg: string` to stderr as debug. */
#define DEBUG(fmt, args...) fprintf(stderr, "[DBG][%s:%d:%s]: " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ##args)
/* Print `msg: string` to stderr as error. Does not exit, unlike `RUNTIME_ASSERT()`. */
#define ERROR(fmt, args...) fprintf(stderr, "[ERR][%s:%d:%s]: " fmt, basename(__FILE__), __LINE__, __FUNCTION__, ##args)

/* Assert that `cond: bool_expression` is true at compile time. */
#define COMPILE_ASSERT(cond) static_assert(cond)
#ifdef _DEBUG
    /* Assert that `cond: bool_expression` is true at runtime. Does nothing if not in debug mode (`-D _DEBUG`). */
    #define RUNTIME_ASSERT(cond) do { if (!(cond)) { fprintf(stderr, "[ERR][%s:%d:%s] Assertion \"%s\" failed.\n", basename(__FILE__), __LINE__, __FUNCTION__, #cond); exit(-1); } } while(0)
#else
    /* Assert that `cond: bool_expression` is true at runtime. Does nothing if not in debug mode (`-D _DEBUG`). */
    #define RUNTIME_ASSERT(cond) IGNORE(cond);
#endif

#define COMPILE_FAIL() COMPILE_ASSERT(1 == 0)

/* Returns true if `x: numeric` is a power of two. */
#define IS_POWER_OF_TWO(x) ({ typeof(x) _x = x; (_x) && !((_x) & ((_x) - 1)); })
/* Returns true if `x: numeric` is a power of two, but without assignments or calls. This is usable at compile time. */
#define IS_POWER_OF_TWO_COMPILE(x) ( (x) && !((x) & ((x) - 1)) )

/* Returns the number of elements in an array. */
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

/* Returns true if `a: float` and `b: float` are within an `epsilon: float` fraction of `a` of each other. */
#define FLOAT_EQ(a, b, epsilon) ({ typeof(a) _a = a; fabs(_a - b) <= epsilon * fabs(_a); })

/* More-intuitive inversion of `memcmp()`. */
#define MEM_EQ(a, b, size) (!memcmp(a, b, size))

/* Force cast `val: any` to `type: type` with no actual conversion; just claim it's a `type`. */
#define FORCE_CAST(val, type) ( *(type*)&val )

/* Combines two tokens, expanding any macros first. */
#define CAT(a, b) CAT_(a, b)
#define CAT_(a, b) a##b

#define NARGS(...) NARGS_(__VA_ARGS__, _8ARG, _7ARG, _6ARG, _5ARG, _4ARG, _3ARG, _2ARG, _1ARG, _0ARG)
#define NARGS_(_8, _7, _6, _5, _4, _3, _2, _1, n, ...) n
    /* Returns a function name for use in a function definition called by `VARARG_CALL()`. */
    #define VARARG_FN_NAME(func, n) func_##n##ARG
    /* Calls a dedicated version of a function for the given number of arguments (see: `VARARG_FN_NAME()`) with said arguments . */
    #define VARARG_CALL(func, ...) CAT(func, NARGS(__VA_ARGS__))(__VA_ARGS__)
#undef NARGS
#undef NARGS_

#endif