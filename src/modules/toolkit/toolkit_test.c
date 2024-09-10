/* === HASH TABLE === */
#if __has_include("toolkit/hashtable.h")
#include "toolkit/hashtable.h"
#include "toolkit/hexdump.h"

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
    DEBUG("`hashtable_contains` test passed.\n");

    /* TEST: Free the hash table and all remaining values. */
    hashtable_free(htable, true);
    DEBUG("`hashtable_free` test passed if you see no leaks.\n");
}
#endif

/* === TIME === */
#if __has_include("toolkit/time.h")
#include "toolkit/time.h"

static void __attribute__((constructor)) test_time(void) {

    /* TEST: Get a timestamp. */
    timestamp_t timestamp = timestamp_get(false);
    
    DEBUG("`timestamp_get` test returns %" TIMESTAMP_FMT " since epoch.\n", timestamp.sec, timestamp.nsec);

    /* TEST: Format a timestamp. */
    char buffer[256];
    timestamp_strftime(buffer, 256, "%Y-%m-%dT%H:%M:%S", timestamp);
    
    DEBUG("`timestamp_strftime` test returns \"%s\" for the previous `timestamp_get` call.\n", buffer);

    /* TEST: Calculate a timestamp difference. */
    timestamp_t tsmono1 = timestamp_get(true);
    timestamp_t tsmono2 = timestamp_get(true);
    timestamp_t timedelta = timestamp_dif(tsmono1, tsmono2);
    
    DEBUG("`timestamp_dif` test returns %" TIMESTAMP_FMT " between calls.\n", timedelta.sec, timedelta.nsec);
}
#endif

/* === DOUBLY LINKED LIST === */
#if __has_include("toolkit/dlinkedlist.h")
#include "toolkit/dlinkedlist.h"

static void __attribute__((constructor)) test_dlinkedlist(void) {
    
    /* TEST: Initialize a doubly linked list. */
    dlinkedlist_t* dlinkedlist = dlinkedlist_init();
    DEBUG("`dlinkedlist_init` test passed.\n");
    
    /* TEST: Push entries to the head of the doubly linked list. */
    for (size_t i = 5; i > 0; i--) {
        int* val = malloc(sizeof(int));
        *val = i*100;
        handle_t handle = {.data = val, .size = sizeof(int)};

        dlinkedlist_push_head(dlinkedlist, handle);
    } /* push [500, ..., 100] to head to get list [100, ..., 500]. */

    RUNTIME_ASSERT(dlinkedlist->entries_n == 5);
    DEBUG("`dlinkedlist_push_head` test passed.\n");

    /* TEST: Push entries to the tail of the doubly linked list. */
    for (size_t i = 6; i < 11; i++) {
        int* val = malloc(sizeof(int));
        *val = i*100;
        handle_t handle = {.data = val, .size = sizeof(int)};

        dlinkedlist_push_tail(dlinkedlist, handle);
    } /* push [600, ..., 1000] to head to get list [100, ..., 1000]. */

    RUNTIME_ASSERT(dlinkedlist->entries_n == 10);
    DEBUG("`dlinkedlist_push_tail` test passed.\n");

    /* TEST: Verify directly that all values were pushed correctly. */
    dlinkedlist_entry_t* entry = dlinkedlist->head;
    for (size_t i = 0; i < 10; i++) {
        int* val = (int*)entry->value.data;

        RUNTIME_ASSERT(*val == (int)(i+1)*100);

        if (entry->next) {
            entry = entry->next;
        }
    }

    DEBUG("`dlinkedlist_push_[...]` tests passed.\n");

    /* TEST: Get values at specific indices. */
    for (size_t i = 0; i < 10; i++) {
        int val1 = (i+1)*100;
        int* val2 = (int*)dlinkedlist_get(dlinkedlist, i).data;

        RUNTIME_ASSERT(val1 == *val2);
    }

    DEBUG("`dlinkedlist_get` test passed.\n");

    /* TEST: Set values at specific indices. */
    for (size_t i = 0; i < 10; i++) {
        int* val1 = malloc(sizeof(int));
        *val1 = (i+1)*1000;
        handle_t handle = {.data = val1, .size = sizeof(int)};

        dlinkedlist_set(dlinkedlist, i, handle, true);

        int* val2 = (int*)dlinkedlist_get(dlinkedlist, i).data;

        RUNTIME_ASSERT(*val1 == *val2);
        
    } /* List is now [1000, ..., 10000]. */

    DEBUG("`dlinkedlist_set` test passed.\n");

    /* TEST: Pop values from the head of the doubly linked list. */
    for (size_t i = 0; i < 3; i++) {
        int* val = (int*)dlinkedlist_pop_head(dlinkedlist).data;

        RUNTIME_ASSERT(*val == (int)(i+1)*1000);

        FREE(val);
    } /* List is now [4000, ..., 10000]. */

    DEBUG("`dlinkedlist_pop_head` test passed.\n");

    /* TEST: Pop values from the tail of the doubly linked list. */
    for (size_t i = 10; i > 7; i--) {
        int* val = (int*)dlinkedlist_pop_tail(dlinkedlist).data;

        RUNTIME_ASSERT(*val == (int)(i)*1000);

        FREE(val);
    } /* List is now [4000, ..., 7000]. */

    DEBUG("`dlinkedlist_pop_tail` test passed.\n");

    /* TEST: Verify length has changed from previous two tests. */
    RUNTIME_ASSERT(dlinkedlist->entries_n == 4);
    
    DEBUG("`dlinkedlist_pop_[...]` tests passed.\n");

    /* TEST: Free a doubly linked list. */
    dlinkedlist_free(dlinkedlist, true);
    
    DEBUG("`dlinkedlist_free` test passed if you see no leaks.\n");
}
#endif

/* === TRANSTEXT === */
#if __has_include("toolkit/transtext.h")
#include "toolkit/transtext.h"

static void __attribute__((constructor)) test_transtext(void) {
    /* TEST: Add reference languages. */
    transtext_reflangs_add("english");
    transtext_reflangs_add("spanish");

    DEBUG("`transtext_reflangs_add` test passed.\n");

    /* TEST: Initialize transtexts. */
    transtext_t* tt_1 = transtext_init();
    transtext_t* tt_2 = transtext_init();

    for (size_t i; i < TTK_TRANSTEXT_LANG_MAXCNT; i++) {
        RUNTIME_ASSERT(tt_2->_translations[i] == NULL);
    }

    DEBUG("`transtext_init` test passed.\n");

    /* TEST: Add some translations to the transtexts. */
    transtext_translation_add(tt_1, "english", "unicode english 😈");
    transtext_translation_add(tt_1, "spanish", "unicode español 😈");
    transtext_translation_add(tt_1, "notalang", "asdfasdfasdf");
    RUNTIME_ASSERT(strcmp(tt_1->_translations[0], "unicode english 😈") == 0);
    RUNTIME_ASSERT(strcmp(tt_1->_translations[1], "unicode español 😈") == 0);

    DEBUG("`transtext_translation_add` test passed.\n");

    /* TEST: Select a language. */
    transtext_reflang_select("spanish");

    DEBUG("`transtext_reflang_select` test passed.\n");

    /* TEST: Get the current translation. */
    RUNTIME_ASSERT(strcmp(transtext_translation_get(tt_1), "unicode español 😈") == 0);
    transtext_reflang_select("english");
    RUNTIME_ASSERT(strcmp(transtext_translation_get(tt_1), "unicode english 😈") == 0);
    transtext_reflang_select("asdfasdfasdf");
    RUNTIME_ASSERT(strcmp(transtext_translation_get(tt_1), "unicode english 😈") == 0);

    DEBUG("`transtext_translation_get` test passed.\n");

    /* TEST: Remove reference langauges. */
    transtext_reflangs_clearall();

    DEBUG("`transtext_reflangs_clearall` test passed.\n");

    /* TEST: Free transtexts. */
    transtext_free(tt_1);
    transtext_free(tt_2);

    DEBUG("`transtext_free` test passed if you see no leaks.\n");
}
#endif