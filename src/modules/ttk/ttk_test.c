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
    DEBUG("`hashtable_contains` test passed.\n");

    /* TEST: Free the hash table and all remaining values. */
    hashtable_free(htable, true);
    DEBUG("`hashtable_free` test passed.\n");
}
#endif

/* === TIME === */
#if __has_include("ttk/time.h")
#include "ttk/time.h"

static void __attribute__((constructor)) test_time(void) {
    timestamp_t timestamp = timestamp_get(false);
    DEBUG("`timestamp_get` test returns %" TIMESTAMP_FMT " since epoch.\n", timestamp.sec, timestamp.nsec);

    char buffer[256];
    timestamp_strftime(buffer, 256, "%Y-%m-%dT%H:%M:%S", timestamp);
    DEBUG("`timestamp_strftime` test returns \"%s\" for the previous `timestamp_get` call.\n", buffer);

    timestamp_t tsmono1 = timestamp_get(true);
    timestamp_t tsmono2 = timestamp_get(true);
    timestamp_t timedelta = timestamp_dif(tsmono1, tsmono2);
    DEBUG("`timestamp_dif` test returns %" TIMESTAMP_FMT " between calls.\n", timedelta.sec, timedelta.nsec);
}
#endif

/* === JSON === */
#if __has_include("ttk/json.h")
#include "ttk/json.h"

static char* json_str = \
"{\n\
    \"languages\": {\n\
        \"supported\": [\"english\", \"german\", \"chinese (simplified)\"],\n\
        \"working on\": [\"spanish\"] \n\
    },\n\
    \"dialogue\": { \n\
        \"main_character_move\": {\n\
            \"english\": \"move forward\",\n\
            \"german\": \"vorwärts gehen\",\n\
            \"chinese (simplified)\": \"前进\"\n\
        },\n\
        \"main_character_attack\": { \n\
            \"english\": \"I split at you.\",\n\
            \"german\": \"Ich habe mich von dir getrennt.\",\n\
            \"chinese (simplified)\": \"我对你分裂了。\"\n\
        }\n\
    },\n\
    \n\
    \"testing_int\": -13,\n\
    \"testing_float\": -19023.123,\n\
    \"testing_array\": [1, 5.3, \"oh god why would you ever mix types\", true, false, {\"wtf\":\"why\"}, null, [1,2,3]],\n\
    \"testing_bool\": true,\n\
    \"testing_other_bool\": false,\n\
    \"testing_null\": null\n\
}\n\0";

static void __attribute__((constructor)) test_json(void) {
    IGNORE(json_str);
}
#endif