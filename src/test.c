/* === HASH TABLE === */
#if __has_include("ttk/hashtable.h") 
#include "ttk/hashtable.h"
#include "ttk/hexdump.h"

static void __attribute__((constructor)) test_hashtable(void) {

    /* TEST: Initialize a hash table. */
    hashtable_t* htable = hashtable_init(100, sizeof(int));

    /* TEST: Add entries to the hash table. */
    for (size_t i = 0; i < 100; i++) {
        int* key = malloc(sizeof(int));
        *key = i+1;
        int* val = malloc(sizeof(int));
        *val = (i+1)*100;

        hashtable_set(htable, key, val, sizeof(int));

        FREE(key);
        FREE(val);
    }

    /* TEST: Get entries from the hash table. */
    for (size_t i = 0; i < 100; i++) {
        int* key = malloc(sizeof(int));
        *key = i+1;
        int* val = hashtable_get(htable, key);
        RUNTIME_ASSERT((*key)*100 == *val);

        FREE(key);
    }

    /* TEST: Display the diagnostics. */
    DEBUG("TEST: Load factor all: %f\n", hashtable_calc_load_factor_all(htable));
    DEBUG("TEST: Load factor buckets: %f\n", hashtable_calc_load_factor_buckets(htable));

    /* TEST: Clean up the hash table. */
    hashtable_free(htable);
}


/* TODO
    - test hashtable.c/hashtable.h
    - write `dynamicarray.c`/`dybamicarray.h`
        - implemented as dynmatically sized c-style array
        - should expose var-arg creation syntax
            - e.g. `dyn_array_init(int, 1, 2, 3, 4, 5)` -> {1,2,3,4,5,0,0,0}
        - should expose set/get index which resizes to power of 2 which fits
            - e.g. `{1,2,3,0}`, set(1, 5) -> `{1,5,3,0}`, set(5, 4) -> {1,5,3,0,0,4,0,0,0}
    - write `doublylinkedlist.c`/`doublylinkedlist.h`
        - tracks head and tail
        - should implement get element by index (with a note to just use an array if this is your goal)
        - should expose `get`/`push`/`pop` to or from either the head or tail
            - this makes it either a stack or a queue!
    - write bit_array? mayble
        - https://en.wikipedia.org/wiki/Bit_array
        - you can bit shift by casting a series of bits to an int, shifting, 
          then comparing to original size's max (e.g. https://stackoverflow.com/questions/8534107/detecting-multiplication-of-uint64-t-integers-overflow-with-c)
        - bit arrays are useful for properties, compression algs, and bloom filters
*/

#endif