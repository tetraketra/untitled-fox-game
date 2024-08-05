#ifndef TTK_HASHTABLE_H
#define TTK_HASHTABLE_H

#include "ttk.h"

typedef struct key_value_pair_t {
    handle_t key; /* any sized key */
    handle_t value; /* any sized value */

    size_t ideal_index; /* if no probing needed to happen */
} key_value_pair_t;

typedef struct hashtable_t {
    key_value_pair_t* buckets; /* key-value pairs */
    size_t capacity; /* capacity */
    size_t count; /* count */

    bool (*key_eq)(handle_t, handle_t);
    float max_load;
} hashtable_t;

extern hashtable_t*     hashtable_init(size_t initial_capacity, bool (*key_eq)(handle_t, handle_t), float max_load);
extern void             hashtable_free(hashtable_t* htable, bool free_values);
extern void             hashtable_insert(hashtable_t* htable, handle_t key, handle_t value, bool free_old_kv_if_overwritten);
extern handle_t         hashtable_lookup(hashtable_t* htable, handle_t key);
extern bool             hashtable_contains(hashtable_t* htable, handle_t key);
extern void             hashtable_remove(hashtable_t* htable, handle_t key, bool free_value, bool free_passed_key_if_removed);

#define KEY_EQ_REQUIRED_BEHAVIOR(key1, key2) do { \
    if ((key1.data == NULL) != (key2.data == NULL)) { return false; } \
    if (key1.data == NULL && key2.data == NULL && key1.size == key2.size) { return true; } \
    if (key1.size != key2.size) { return false; } \
    } while (0)

#endif