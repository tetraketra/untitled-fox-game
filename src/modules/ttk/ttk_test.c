/* === HASH TABLE === */
#if __has_include("ttk/hashtable.h")
#include "ttk/hashtable.h"
#include "ttk/hexdump.h"

static void __attribute__((constructor)) test_hashtable(void) {

    /* TEST: Initialize a hash table. */
    hashtable_t* htable = hashtable_init(100, NULL, 0.8);
    RUNTIME_ASSERT(htable->capacity == 100);
    RUNTIME_ASSERT(htable->count == 0);
    RUNTIME_ASSERT(htable->max_load == 0.8f);
    DEBUG("`hashtable_init` test passed.\n");

    /* TEST: Insert some handles to trigger some rehashes. */
    DEBUG("`hashtable_insert` test starting. Expect 5 rehashes.\n");
    for (int i = 0; i < 2000; i++) {
        int* heap_int_key = malloc(sizeof(int));
        *heap_int_key = i;

        int* heap_int_val = malloc(sizeof(int));
        *heap_int_val = i*100;

        handle_t key = {.data = heap_int_key, .size=sizeof(int)};
        handle_t val = {.data = heap_int_val, .size=sizeof(int)};

        hashtable_insert(htable, key, val, true);
    }

    RUNTIME_ASSERT(htable->capacity == 3200);
    RUNTIME_ASSERT(htable->count == 2000);
    RUNTIME_ASSERT(htable->max_load == 0.8f);
    DEBUG("`hashtable_insert` test passed.\n");

    /* TEST: Get all keys just inserted. */
    for (int i = 0; i < 2000; i++) {
        int* heap_int_key = malloc(sizeof(int));
        *heap_int_key = i;

        handle_t key = {.data = heap_int_key, .size=sizeof(int)};

        handle_t fetched_val = hashtable_lookup(htable, key);
        RUNTIME_ASSERT(*(int*)fetched_val.data == i*100);

        free(heap_int_key);
        
    }

    RUNTIME_ASSERT(htable->capacity == 3200);
    RUNTIME_ASSERT(htable->count == 2000);
    RUNTIME_ASSERT(htable->max_load == 0.8f);
    DEBUG("`hashtable_lookup` test passed.\n");

    /* TEST: Get and delete only some elements. */
    for (int i = 0; i < 1000; i++) {
        int* heap_int_key = malloc(sizeof(int));
        *heap_int_key = i;

        handle_t key = {.data = heap_int_key, .size=sizeof(int)};

        hashtable_remove(htable, key, true, false);

        handle_t fetched_val = hashtable_lookup(htable, key);
        RUNTIME_ASSERT(fetched_val.data == NULL);

        free(key.data);
    }

    RUNTIME_ASSERT(htable->capacity == 3200);
    RUNTIME_ASSERT(htable->count == 1000);
    RUNTIME_ASSERT(htable->max_load == 0.8f);
    DEBUG("`hashtable_remove` test passed.\n");

    /* TEST: Insert new values for all elements. */
    for (int i = 0; i < 2000; i++) {
        int* heap_int_key = malloc(sizeof(int));
        *heap_int_key = i;

        int* heap_int_val = malloc(sizeof(int));
        *heap_int_val = i*1000;

        handle_t key = {.data = heap_int_key, .size=sizeof(int)};
        handle_t val = {.data = heap_int_val, .size=sizeof(int)};

        hashtable_insert(htable, key, val, true);
        
        handle_t fetched_val = hashtable_lookup(htable, key);
        RUNTIME_ASSERT(*(int*)fetched_val.data == i*1000);
    }
    
    RUNTIME_ASSERT(htable->capacity == 3200);
    RUNTIME_ASSERT(htable->count == 2000);
    RUNTIME_ASSERT(htable->max_load == 0.8f);
    DEBUG("`hashtable_insert` overwriting test passed.\n");

    /* TEST: Check all keys exist. */
    for (int i = 0; i < 2000; i++) {
        int* heap_int_key = malloc(sizeof(int));
        *heap_int_key = i;

        handle_t key = {.data = heap_int_key, .size=sizeof(int)};

        bool does_contain = hashtable_contains(htable, key);
        RUNTIME_ASSERT(does_contain);

        FREE_HANDLE_SAFELY_WITH_FALLBACK(key);
    }

    for (int i = 2000; i < 4000; i++) {
        int* heap_int_key = malloc(sizeof(int));
        *heap_int_key = i;

        handle_t key = {.data = heap_int_key, .size=sizeof(int)};

        bool does_contain = hashtable_contains(htable, key);
        RUNTIME_ASSERT(!does_contain);

        FREE_HANDLE_SAFELY_WITH_FALLBACK(key);  
    }

    RUNTIME_ASSERT(htable->capacity == 3200);
    RUNTIME_ASSERT(htable->count == 2000);
    RUNTIME_ASSERT(htable->max_load == 0.8f);
    DEBUG("`hashtable_insert` overwriting test passed.\n");

    /* TEST: Free the hash table and all remaining values. */
    hashtable_free(htable, true);
    DEBUG("`hashtable_free` test passed.\n");
}
#endif

/* === DOUBLY LINKED LIST === */
#if false && __has_include("ttk/dlinkedlist.h")
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

    /* TEST: Verify length has changed from previous two tests. */
    RUNTIME_ASSERT(dlinkedlist->entries_n == 4);

    /* TEST: Free a doubly linked list. */
    dlinkedlist_free(dlinkedlist);
}
#endif