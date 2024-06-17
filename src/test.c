/* === HASH TABLE === */
#if __has_include("ttk/hashtable.h")
#include "ttk/hashtable.h"
#include "ttk/hexdump.h"

static void __attribute__((constructor)) test_hashtable(void) {

    /* TEST: Initialize a hash table. */
    hashtable_t* htable = hashtable_init(10, sizeof(int));

    /* TEST: Add entries. */
    for (size_t i = 0; i < 10000; i++) {
        int key = i;
        int val = i * 10;

        hashtable_set(htable, &key, &val, sizeof(int));
    }

    /* TEST: Check and get entries. */
    for (size_t i = 0; i < 10000; i++) {
        int key = i;
        int val = i * 10;

        RUNTIME_ASSERT(hashtable_has(htable, &key));
        RUNTIME_ASSERT(*(int*)hashtable_get(htable, &key) == val);
    }

    /* TEST: Check the load factors. */
    RUNTIME_ASSERT(FLOAT_EQ(hashtable_calc_load_factor(htable), 1000.0f, 0.01f));
    RUNTIME_ASSERT(FLOAT_EQ(hashtable_calc_bucket_usage(htable), 1.0f, 0.01f));

    /* TEST: Remove some entries without side effects. */
    for (size_t i = 0; i < 10000; i++) {
        int key = i;

        if (i % 2 == 0) {
            hashtable_rid(htable, &key);
        }
    }

    for (size_t i = 0; i < 10000; i++) {
        int key = i;
        int val = i * 10;

        if (i % 2 == 0) {
            RUNTIME_ASSERT(!hashtable_has(htable, &key));
            RUNTIME_ASSERT(hashtable_get(htable, &key) == NULL);
        } else {
            RUNTIME_ASSERT(hashtable_has(htable, &key));
            RUNTIME_ASSERT(*(int*)hashtable_get(htable, &key) == val);
        }
    }

    /* TEST: Overwrite all values and write new values. */
    for (size_t i = 0; i < 10000; i++) {
        int key = i;
        int val = i * 100;

        hashtable_set(htable, &key, &val, sizeof(int));

        RUNTIME_ASSERT(hashtable_has(htable, &key));
        RUNTIME_ASSERT(*(int*)hashtable_get(htable, &key) == val);
    }

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