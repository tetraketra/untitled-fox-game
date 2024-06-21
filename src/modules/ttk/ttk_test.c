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
#endif


/* === DOUBLY LINKED LIST === */
#if __has_include("ttk/dlinkedlist.h")
#include "ttk/dlinkedlist.h"

static void __attribute__((constructor)) test_dlinkedlist(void) {
    
    /* TEST: Initialize a doubly linked list. */
    dlinkedlist_t* dlinkedlist = dlinkedlist_init();
    
    /* TEST: Push entries to the head of the doubly linked list. */
    for (size_t i = 5; i > 0; i--) {
        int val = i*100;

        dlinkedlist_push_head(dlinkedlist, &val, sizeof(int));
    } /* push [500, ..., 100] to head to get list [100, ..., 500]. */

    RUNTIME_ASSERT(dlinkedlist->entries_n == 5);

    /* TEST: Push entries to the tail of the doubly linked list. */
    for (size_t i = 6; i < 11; i++) {
        int val = i*100;

        dlinkedlist_push_tail(dlinkedlist, &val, sizeof(int));
    } /* push [600, ..., 1000] to head to get list [100, ..., 1000]. */

    RUNTIME_ASSERT(dlinkedlist->entries_n == 10);

    /* TEST: Verify directly that all values were pushed correctly. */
    dlinkedlist_entry_t* entry = dlinkedlist->head;
    for (size_t i = 0; i < 10; i++) {
        int* val = (int*)entry->data;

        RUNTIME_ASSERT(*val == (int)(i+1)*100);

        entry = entry->next;
    }

    /* TEST: Get values at specific indices. */
    for (size_t i = 0; i < 10; i++) {
        int val1 = (i+1)*100;
        int* val2 = (int*)dlinkedlist_get(dlinkedlist, i);

        RUNTIME_ASSERT(val1 == *val2);
    }

    /* TEST: Set values at specific indices. */
    for (size_t i = 0; i < 10; i++) {
        int val1 = (i+1)*1000;

        dlinkedlist_set(dlinkedlist, i, &val1, sizeof(int));

        int* val2 = (int*)dlinkedlist_get(dlinkedlist, i);

        RUNTIME_ASSERT(val1 == *val2);
    } /* List is now [1000, ..., 10000]. */

    /* TEST: Pop values from the head of the doubly linked list. */
    for (size_t i = 0; i < 3; i++) {
        int* val = (int*)dlinkedlist_pop_head(dlinkedlist);

        RUNTIME_ASSERT(*val == (int)(i+1)*1000);

        FREE(val);
    } /* List is now [4000, ..., 10000]. */

    /* TEST: Pop values from the tail of the doubly linked list. */
    for (size_t i = 10; i > 7; i--) {
        int* val = (int*)dlinkedlist_pop_tail(dlinkedlist);

        RUNTIME_ASSERT(*val == (int)(i)*1000);

        FREE(val);
    } /* List is now [4000, ..., 7000]. */

    /* TEST: Verify length has changed. */
    RUNTIME_ASSERT(dlinkedlist->entries_n == 4);

    /* TEST: Free the doubly linked list. */
    dlinkedlist_free(dlinkedlist);
}
#endif

/* TODO
    - write `dynamicarray.c`/`dybamicarray.h`
        - implemented as dynmatically sized c-style array
        - should expose var-arg creation syntax
            - e.g. `dyn_array_init(int, 1, 2, 3, 4, 5)` -> {1,2,3,4,5,0,0,0}
        - should expose set/get index which resizes to power of 2 which fits
            - e.g. `{1,2,3,0}`, set(1, 5) -> `{1,5,3,0}`, set(5, 4) -> {1,5,3,0,0,4,0,0,0}
    - write bit_array? maybe
        - ** maybe also a specific-length packing system? like "adjacent 5bit numbers" **
        - https://en.wikipedia.org/wiki/Bit_array
        - you can bit shift by casting a series of bits to an int, shifting,
          then comparing to original size's max (e.g. https://stackoverflow.com/questions/8534107/detecting-multiplication-of-uint64-t-integers-overflow-with-c)
        - bit arrays are useful for properties, compression algs, and bloom filters
*/



